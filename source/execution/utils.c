/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:22:36 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/08 15:44:30 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

void	close_pipes_files(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close (data->pipe_fd[i][0]);
		close (data->pipe_fd[i][1]);
		i++;
	}
}

void	waitpid_forks(t_exec *data, int *status)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		waitpid(data->fork_pid[i], &(*status), 0);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			*status = WTERMSIG(*status) + 128;
		i++;
	}
}

int	create_fork_pipe(t_exec *data, t_pl *parser, int i)
{
	if (i < data->num_commands - 1)
	{
		if (pipe(data->pipe_fd[i]) < 0)
		{
			error_seterrno("pipe", "Resource temporarily unavailable", errno);
			free_data(data, parser);
			return (-1);
		}
	}
	data->fork_pid[i] = fork();
	if (data->fork_pid[i] == -1)
	{
		error_seterrno("pipe", "Resource temporarily unavailable", errno);
		free_data(data, parser);
		return (-1);
	}
	return (0);
}

char	**copy_environment_list(char **env)
{
	int			i;
	char		**new_environ;

	i = 0;
	while (env[i])
		i++;
	new_environ = null_check(malloc ((i + 1) * sizeof (char *)));
	i = 0;
	while (env[i])
	{
		new_environ[i] = null_check(ft_strdup(env[i]));
		i++;
	}
	new_environ[i] = NULL;
	return (new_environ);
}

int	array_size(char **array)
{
	int	count;

	if (!array)
		return (-1);
	count = 0;
	while (array[count])
		count++;
	return (count);
}
