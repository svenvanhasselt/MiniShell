/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/20 17:46:42 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	redirection(t_exec *data);
void	*prepare(t_parser_list *p_list);
void	execute(t_exec *data, int fdin, int fdout, int i);	
void	*testing(t_exec *data);
char	*path_cmd(char *command, char **env);
int		check_builtins(char **cmd_table, t_exec **data);
void	create_cmd_table(t_parser_list **p_list);

int	execution(t_parser_list **p_list)
{
	int				i;
	t_exec			*data;

	data = prepare(*p_list);
	data = testing(data);
	create_cmd_table(p_list);
	// while((*p_list))
	// {
	// 	i = 0;
	// 	// printf("%s\n", (*p_list)->lst->str);
	// 	while ((*p_list)->cmd_table[i])
	// 	{
	// 		printf("%s\n", (*p_list)->cmd_table[i]);
	// 		i++;
	// 	}
	// 	(*p_list) = (*p_list)->next;
	// }
	redirection(data);
	i = 0;
	if (check_builtins(data->test_cmd[0], &data))
		i++;
	create_pipes(data, data->num_commands - i);
	while (i < data->num_commands)
	{
		data->fork_pid[i] = fork();
		if (data->fork_pid[i] == -1)
			error_exit("operation failure", errno);
		if (data->num_commands == 1 && data->fork_pid[i] == 0)
			execute(data, data->fdin, data->fdout, i);
		else if (i == 0 && data->fork_pid[i] == 0)
			execute(data, data->fdin, data->pipe_fd[i][1], i);
		else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
			execute(data, data->pipe_fd[i - 1][0], data->fdout, i);
		else if (data->fork_pid[i] == 0)
			execute(data, data->pipe_fd[i - 1][0], data->pipe_fd[i][1], i);
		i++;
	}
	close_pipes_files(data);
	waitpid_forks(data);
	return(data->exit_status);
}

int	lst_size(t_parser_node	*lst)
{
	int				count;
	t_parser_node	*current;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		current = current->nxt_node;
		count++;
	}
	return (count);
}

int	lst_size_p(t_parser_list	*lst)
{
	int				count;
	t_parser_list	*current;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void	create_cmd_table(t_parser_list **p_list)
{
	int	i;
	int	size;
	t_parser_list *head;

	head = *p_list;
	while(head)
	{
		i = 0;
		size = lst_size(head->lst);
		head->cmd_table = null_check(malloc ((size + 1) * sizeof(char *)));
		while (head->lst)
		{
			head->cmd_table[i] = head->lst->str;
			head->lst = head->lst->nxt_node;
			i++;
		}
		head->cmd_table[i] = NULL;
		head = head->next;
	}
}

void	*prepare(t_parser_list *p_list)
{
	int			i;
	t_exec		*data;
	extern char	**environ;

	data = null_check(malloc (1 * sizeof(t_exec)));
	data->num_commands = lst_size_p(p_list);
	data->infile = 0;
	data->outfile = 0;
	data->fork_pid = null_check(malloc(data->num_commands * sizeof(int)));
	data->pipe_fd = null_check(malloc ((data->num_commands - 1) * sizeof(int *)));
	i = -1;
	while (++i < data->num_commands - 1)
		data->pipe_fd[i] = null_check(malloc (2 * sizeof(int)));
	data->env = copy_environment_list(environ);
	return (data);
}

void	redirection(t_exec *data)
{
	if (data->infile)
	{
		data->fdin = open("test_in", O_RDONLY);
		if (!data->fdin)
			error_exit("ADD INFILE", errno);
	}
	else
		data->fdin = STDIN_FILENO;
	if (data->outfile)
	{
		data->fdout = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!data->fdout)
			error_exit("ADD OUTFILE", errno);
	}
	else
		data->fdout = STDOUT_FILENO;
}

void	execute(t_exec *data, int fdin, int fdout, int i)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
	close_pipes_files(data);
	if (check_builtins(data->test_cmd[i], &data))
		exit (data->exit_status);
	execve(path_cmd(data->test_cmd[i][0], data->env), \
	data->test_cmd[i], data->env);
	if (errno != EACCES)
		error_exit(data->test_cmd[i][0], ERR_NO_CMD);
	error_exit(data->test_cmd[i][0], errno);
}

char	*path_cmd(char *command, char **env)
{
	int			i;
	char		**paths;
	char		*cmd_path;

	if (ft_strchr(command, '/'))
		return (command);
	i = find_env_var("PATH", env);
	if (i >= 0)
		paths = null_check(ft_split(env[i] + find_value(env[i]) + 1, ':'));
	else
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = null_check(ft_strjoin(paths[i], "/"));
		cmd_path = null_check(ft_strjoin_free(cmd_path, command));
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (command);
}

int	check_builtins(char **cmd_table, t_exec **data)
{
	int	i;
	int	status;

	i = -1;
	while (cmd_table[0][++i])
		cmd_table[0][i] = ft_tolower(cmd_table[0][i]);
	if (strncmp(cmd_table[0], "cd", ft_strlen(cmd_table[0])) == 0)
		status = cd_builtin(cmd_table, &(*data)->env);
	else if (strncmp(cmd_table[0], "echo", ft_strlen(cmd_table[0])) == 0)
		status = echo_builtin(cmd_table);
	else if (strncmp(cmd_table[0], "env", ft_strlen(cmd_table[0])) == 0)
		status = env_builtin((*data)->env);
	else if (strncmp(cmd_table[0], "exit", ft_strlen(cmd_table[0])) == 0)
		status = exit_builtin(666);
	else if (strncmp(cmd_table[0], "export", ft_strlen(cmd_table[0])) == 0)
		status = export_builtin(cmd_table, &(*data)->env);
	else if (strncmp(cmd_table[0], "pwd", ft_strlen(cmd_table[0])) == 0)
		status = pwd_builtin();
	else if (strncmp(cmd_table[0], "unset", ft_strlen(cmd_table[0])) == 0)
		status = unset_builtin(cmd_table[1], &(*data)->env);
	else
		return (0);
	(*data)->exit_status = status;
	return (1);
}

void	*testing(t_exec *data)
{
	data->test_cmd[0][0] = ft_strdup("bash");
	data->test_cmd[0][1] = NULL;
	data->test_cmd[0][2] = NULL;
	data->test_cmd[0][3] = NULL;
	data->test_cmd[1][0] = ft_strdup("export");
	data->test_cmd[1][1] = NULL;
	data->test_cmd[1][2] = NULL;
	// data->test_cmd[2][0] = ft_strdup("export");
	// data->test_cmd[2][1] = ft_strdup("S=46");
	// data->test_cmd[2][2] = ft_strdup("S=48");
	// data->test_cmd[2][3] = NULL;
	return (data);
}
