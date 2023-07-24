/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/21 18:21:02 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	execute(t_exec *data);
char	*path_cmd(char *command, char **env);
int		check_builtins(char **cmd_table, t_exec **data);

int	execution(t_parser_list **p_list, char ***env)
{
	int				i;
	t_exec			*data;
	t_parser_list	*parser;
	
	ft_putstr_fd("\n\n\n-----------MiniShell Output-------------\n", 1);
	parser = *p_list;
	data = prepare(parser, (*env));
	i = 0;
	if (check_builtins(parser->cmd_table, &data))
		i++;
	create_pipes(data, data->num_commands - i);
	while (i < data->num_commands)
	{
		data->fork_pid[i] = fork();
		if (data->fork_pid[i] == -1)
			error_exit("operation failure", errno);
		redirection(parser, data, i);
		if (data->num_commands == 1 && data->fork_pid[i] == 0)
			execute(data);
		else if (i == 0 && data->fork_pid[i] == 0)
			execute(data);
		else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
			execute(data);
		else if (data->fork_pid[i] == 0)
			execute(data);
		parser = parser->next;
		i++;
	}
	close_pipes_files(data);
	waitpid_forks(data);
	ft_putstr_fd("Return code: ", 1);
	ft_putnbr_fd(data->exit_status, 1);
	ft_putstr_fd("\n-----------MiniShell Output-------------\n\n\n", 1);
	return (data->exit_status);
}

void	create_cmd_table(t_parser_list *parser)
{
	int				i;
	int				size;
	t_parser_list	*head;

	head = parser;
	while (head)
	{
		i = 0;
		size = ft_sizelist_parser(head->lst);
		head->cmd_table = null_check(malloc ((size + 1) * sizeof(char *)));
		while (head->lst)
		{
			head->cmd_table[i] = head->lst->str;
			head->lst = head->lst->next;
			i++;
		}
		head->cmd_table[i] = NULL;
		head = head->next;
	}
}

void	execute(t_exec *data)
{
	if (dup2(data->fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(data->fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
	close_pipes_files(data);
	if (check_builtins(data->cmd_table, &data))
		exit (data->exit_status);
	execve(path_cmd(data->cmd_table[0], data->env), \
	data->cmd_table, data->env);
	if (errno != EACCES)
		error_exit(data->cmd_table[0], ERR_NO_CMD);
	error_exit(data->cmd_table[0], errno);
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
	i = -1;
	while (paths[++i])
	{
		cmd_path = null_check(ft_strjoin(paths[i], "/"));
		cmd_path = null_check(ft_strjoin_free(cmd_path, command));
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
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
		status = exit_builtin();
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
