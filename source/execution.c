/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/15 18:26:15 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

typedef	struct exec_struc
{
	int		infile;
	int		outfile;
	int		fdin;
	int		fdout;
	int num_commands;
}	t_exec;

void	redirection(int file, int tmpfd, int *fd);
void	prepare(t_exec *data);

void	execution(void)
{
	t_exec	*data;
	int		tmp_in;
	int		tmp_out;
	int		pipe_fd[2];
	int		*fork_id;
	int		i;
	char 	*test_s;

	test_s = NULL;
	data = malloc (1 * sizeof(t_exec));
	if (!data)
		exit (1);
	prepare(data);
	fork_id = malloc(data->num_commands * sizeof(int));
	if (!fork_id)
		exit (1);
	tmp_in = dup(0);
	tmp_out = dup(1);
	redirection(data->infile, tmp_in, &data->fdin);
	i = 0;
	while (i < data->num_commands)
	{
		if (i == data->num_commands - 1)
		{
			redirection(data->outfile, tmp_out, &data->fdout);
			fork_id[i] = fork();
			if (fork_id[i] == -1)
				exit (1);
			if (fork_id[i] == 0)
			{
				printf("In child\n");
				exit(0);
			}
		}
		else
		{
			if (pipe(pipe_fd) == -1)
				exit (1);
			data->fdin = dup(pipe_fd[0]);
			data->fdout = dup(pipe_fd[1]);
			fork_id[i] = fork();
			if (fork_id[i] == -1)
				exit (1);
			if (fork_id[i] == 0)
			{
				printf("In child\n");
			
				write(pipe_fd[1], "Testing!", 8);
				read(pipe_fd[0], test_s, 8);
				write(2, test_s, 8);
				close (pipe_fd[0]);
				close (pipe_fd[1]);
				exit(0);
			}
		}
		i++;
	}
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	i = 0;
	while (i < data->num_commands)
	{
		waitpid(fork_id[i], NULL, 0);
		i++;
	}
}

void	prepare(t_exec *data)
{
	data->num_commands = 5;
	data->infile = 0;
}

void	redirection(int file, int tmpfd, int *fd)
{
	if (file)
	{
		*fd = open("test", O_RDONLY);
		if (!*fd)
			exit(1);
	}
	else
	{
		*fd = dup(tmpfd);
		if (!*fd)
			exit(1);
	}

}