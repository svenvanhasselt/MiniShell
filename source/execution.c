/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/20 16:24:58 by svan-has      ########   odam.nl         */
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
	int 	num_commands;
	int		**pipe_fd;
	int		*fork_id;
}	t_exec;

// void	redirection(int file, int tmpfd, int *fd);
void	*prepare(void);
void	close_pipes(t_exec	*data);
void	waitpid_forks(t_exec *data);
void	create_pipes_forks(t_exec *data);

void	execution(void)
{
	t_exec	*data;
	int		i;

	data = prepare();
	if (data->infile)
	{
		data->fdin = open("test_in", O_RDONLY);
		if (!data->fdin)
			exit(1);
	}
	else
		data->fdin = STDIN_FILENO;
	if (data->outfile)
	{
		data->fdout = open("test", O_WRONLY);
		if (!data->fdout)
			exit(1);
	}
	else
		data->fdout = STDOUT_FILENO;
	create_pipes_forks(data);
	i = 0;
	while (i < data->num_commands)
	{
		if (i == 0 && data->fork_id[i] == 0)
		{
			if (dup2(data->fdin, STDIN_FILENO) < 0)
				exit (1);
			if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) < 0)
				exit (1);
			write(2, "Testing!\n", 9);

			close_pipes(data);
			exit(0);
		}
		if (i == 0 && data->fork_id[i] == 0)
			exit (0);
		else if (i == data->num_commands - 1 && data->fork_id[i] == 0)
		{
			if (dup2(data->fdout, STDOUT_FILENO) < 0)
				exit (1);
			if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) < 0)
				exit (1);
			close_pipes(data);
			exit(0);
		}
		else if (data->fork_id[i] == 0)
		{
			if (dup2(data->pipe_fd[i - 1][0], STDIN_FILENO) < 0)
				exit (1);
			if (dup2(data->pipe_fd[i][1], STDOUT_FILENO) < 0)
				exit (1);
			char *test;
			test = malloc (9 * sizeof(char));
			read (STDIN_FILENO, test, 9);
			write (2, test, 9);
			close_pipes(data);
			exit(0);
		}
		i++;
	}
	close_pipes(data);
	waitpid_forks(data);
}

void	*prepare(void)
{
	int		i;
	t_exec	*data;

	data = malloc (1 * sizeof(t_exec));
	if (!data)
		exit (1);
	data->num_commands = 5;
	data->infile = 0;
	data->outfile = 0;
	data->fork_id = malloc(data->num_commands * sizeof(int));
	if (!data->fork_id)
		exit (1);
	i = 0;
	data->pipe_fd = (int **) malloc ((data->num_commands - 1) * sizeof(int *));
	while (i < data->num_commands - 1)
	{
		data->pipe_fd[i] = (int *) malloc (2 * sizeof(int));
		if (!data->pipe_fd[i])
			exit (1);
		i++;
	}
	return (data);
}

// void	redirection(int file, int tmpfd, int *fd)
// {
// 	int	file_fd;

// 	if (file)
// 	{
// 		file_fd = open("test", O_RDONLY);
// 		if (!file_fd)
// 			exit(1);
// 		if (dup2(file_fd, *fd) < 0)
// 			exit (1);
// 	}
// 	else
// 		return ;
// }

void	close_pipes(t_exec	*data)
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

void	waitpid_forks(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		waitpid(data->fork_id[i], NULL, 0);
		i++;
	}
}

void	create_pipes_forks(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		data->fork_id[i] = fork();
		if (data->fork_id[i] == -1)
			exit (1);
		if (i < data->num_commands - 1)
		{
			if (pipe(data->pipe_fd[i]) < 0)
				exit (1);
		}
		i++;	
	}
}