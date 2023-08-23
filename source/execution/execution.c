/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/23 12:44:23 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	execute(t_exec *data, char ***env);
char	*path_cmd(char *command, char **env);
int		check_builtins(char **cmd_table, char ***env, int *status, int prev_status);
void	dup2_stdin_stdout(int fdin, int fdout);
int		builtins_redirect(t_exec **data, t_pl *parser, char ***env);

void	execute_command(t_exec *data, char ***env, int i)
{
	if (data->num_commands == 1 && data->fork_pid[i] == 0)
		execute(data, env);
	else if (i == 0 && data->fork_pid[i] == 0)
		execute(data, env);
	else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
		execute(data, env);
	else if (data->fork_pid[i] == 0)
		execute(data, env);
}

int	redirection_error(t_exec *data, int i)
{
	if (data->fdin < 0 || data->fdout < 0)
	{
		data->exit_status = 1;
		if (data->fork_pid[i] == 0)
			exit (1);
		return (1);
	}
	return (0);
}

int	execution(t_pl **p_list, char ***env, int prev_status)
{
	int				i;
	t_exec			*data;
	t_pl	*parser;

	parser = *p_list;
	data = prepare(&parser, env);
	data->prev_status = prev_status;
	if (builtins_redirect(&data, parser, env) >= 0)
		return (data->exit_status);
	i = 0;
	create_pipes(data, data->num_commands);
	while (i < data->num_commands)
	{
		data->fork_pid[i] = fork();
		if (data->fork_pid[i] == -1)
			error_exit("operation failure", errno);
		redirection(parser, data, i);
		if (!redirection_error(data, i))
			execute_command(data, env, i);
		parser = parser->next;
		i++;
	}
	close_pipes_files(data);
	waitpid_forks(data);
	return (data->exit_status);
}

void	create_cmd_table(t_pl *parser)
{
	int				i;
	int				size;
	t_pl			*head;
	t_pn			*head_lst;

	head = parser;
	while (head)
	{
		i = 0;
		head_lst = head->lst;
		size = ft_sizelist_parser(head_lst);
		head->cmd_table = null_check(malloc ((size + 1) * sizeof(char *)));
		while (head_lst)
		{
			if (head_lst->str)
				head->cmd_table[i] = head_lst->str;
			else
				head->cmd_table[i] = NULL;
			head_lst = head_lst->next;
			i++;
		}
		head->cmd_table[i] = NULL;
		head = head->next;
	}
}


void	execute(t_exec *data, char ***env)
{
	signals_default();
	if (dup2(data->fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(data->fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
	close_pipes_files(data);
	if (check_builtins(data->cmd_table, env, &data->exit_status, data->prev_status))
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

int	check_builtins(char **cmd_table, char ***env, int *status, int prev_status)
{
	int	i;

	i = -1;
	if (!cmd_table[0])
		return (-1);
	while (cmd_table[0][++i])
		cmd_table[0][i] = ft_tolower(cmd_table[0][i]);
	if (strncmp(cmd_table[0], "cd", ft_strlen(cmd_table[0])) == 0)
		*status = cd_builtin(cmd_table, env);
	else if (strncmp(cmd_table[0], "echo", ft_strlen(cmd_table[0])) == 0)
		*status = echo_builtin(cmd_table);
	else if (strncmp(cmd_table[0], "env", ft_strlen(cmd_table[0])) == 0)
		*status = env_builtin((*env));
	else if (strncmp(cmd_table[0], "exit", ft_strlen(cmd_table[0])) == 0)
		*status = exit_builtin(cmd_table, prev_status);
	else if (strncmp(cmd_table[0], "export", ft_strlen(cmd_table[0])) == 0)
		*status = export_builtin(cmd_table, env);
	else if (strncmp(cmd_table[0], "pwd", ft_strlen(cmd_table[0])) == 0)
		*status = pwd_builtin();
	else if (strncmp(cmd_table[0], "unset", ft_strlen(cmd_table[0])) == 0)
		*status = unset_builtin(cmd_table[1], env);
	else
		return (0);
	return (1);
}

void	dup2_stdin_stdout(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
}

int	builtins_redirect(t_exec **data, t_pl *parser, char ***env)
{
	int	*status;

	status = &(*data)->exit_status;
	if ((*data)->num_commands == 1)
	{
		(*data)->fdin_old = dup(STDIN_FILENO);
		(*data)->fdout_old = dup(STDOUT_FILENO);
		(*data)->fdin = redirect(parser, status, STDIN_FILENO, true);
		(*data)->fdout = redirect(parser, status, STDOUT_FILENO, false);
		if ((*data)->fdin < 0 || (*data)->fdout < 0)
			return (*status);
		dup2_stdin_stdout((*data)->fdin, (*data)->fdout);
		if (check_builtins(parser->cmd_table, env, status, (*data)->prev_status))
		{
			dup2_stdin_stdout((*data)->fdin_old, (*data)->fdout_old);
			return (*status);
		}
		dup2_stdin_stdout((*data)->fdin_old, (*data)->fdout_old);
	}
	return (-1);
}
