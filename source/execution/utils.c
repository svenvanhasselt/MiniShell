/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:22:36 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/12 17:56:10 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

void	close_pipes(t_exec *data)
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

void	close_pipes_child(t_exec *data, int i)
{
	int	pipe;

	pipe = 0;
	while (pipe < data->num_commands - 1 && data->pipe_fd[pipe][0] != 0)
	{
		if (pipe + 1 != i)
			close (data->pipe_fd[pipe][0]);
		if (pipe != i)
			close (data->pipe_fd[pipe][1]);
		pipe++;
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
