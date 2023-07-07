/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:22:36 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/07 18:32:40 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

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
	if (data->infile && i == 0)
		close(data->fdin);
	if (data->outfile && i == data->num_commands - 1)
		close(data->fdout);
}

void	waitpid_forks(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		waitpid(data->fork_pid[i], &data->exit_status, 0);
		i++;
	}
	if (WIFEXITED(data->exit_status))
        data->exit_status = WEXITSTATUS(data->exit_status);
}

void	create_pipes(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		if (i < data->num_commands - 1)
		{
			if (pipe(data->pipe_fd[i]) < 0)
				exit (1);
		}
		i++;
	}
}

// void	builtin_func(t_exec *data)
// {
// 	data->builtin_func[0]->name = "echo";
// 	data->builtin_func[0]->func = &echo;
// 	data->builtin_func[1]->name = "cd";
// 	data->builtin_func[1]->func = &cd;
// 	data->builtin_func[2]->name = "pwd";
// 	data->builtin_func[2]->func = &pwd;
// 	data->builtin_func[3]->name = "export";
// 	data->builtin_func[3]->func = &export;
// 	data->builtin_func[4]->name = "unset";
// 	data->builtin_func[4]->func = &unset;
// 	data->builtin_func[5]->name = "env";
// 	data->builtin_func[5]->func = &env;
// 	data->builtin_func[6]->name = "echo";
// 	data->builtin_func[6]->func = &exit_builtin;
// }

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
