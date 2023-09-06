/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/06 17:07:27 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	execute(t_exec *data, char ***env, int *status);
char	*path_cmd(char *command, char **env);
void	execute_command(t_exec *data, char ***env, int i, int *status);
int		redirection_error(t_exec *data, int i, int *status);

void	execution(t_pl **p_list, char ***env, int *status)
{
	int		i;
	t_exec	*data;
	t_pl	*parser;

	parser = *p_list;
	data = prepare(&parser, env);
	data->exit_status = status;
	if (builtins_redirect(&data, parser, env, status) >= 0)
		return ;
	i = 0;
	while (i < data->num_commands)
	{
		if (create_fork_pipe(data, parser, i) < 0)
			return ;
		redirection(parser, data, i);
		if (!redirection_error(data, i, status))
			execute_command(data, env, i, status);
		parser = parser->next;
		i++;
	}
	close_pipes_files(data);
	waitpid_forks(data, status);
	free_data(data, parser);
}

void	execute_command(t_exec *data, char ***env, int i, int *status)
{	
	signals_child();
	if (data->num_commands == 1 && data->fork_pid[i] == 0)
		execute(data, env, status);
	else if (i == 0 && data->fork_pid[i] == 0)
		execute(data, env, status);
	else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
		execute(data, env, status);
	else if (data->fork_pid[i] == 0)
		execute(data, env, status);
}

int	redirection_error(t_exec *data, int i, int *status)
{
	if (data->fdin < 0 || data->fdout < 0)
	{
		*status = 1;
		if (data->fork_pid[i] == 0)
			exit (1);
		return (1);
	}
	return (0);
}

void	execute(t_exec *data, char ***env, int *status)
{
	if (dup2(data->fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(data->fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
	close_pipes_files(data);
	if (check_builtins(data->cmd_table, env, status))
		exit (*status);
	execve(path_cmd(data->cmd_table[0], *env), data->cmd_table, *env);
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
