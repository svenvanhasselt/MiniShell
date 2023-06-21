/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:35:16 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/21 12:35:34 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

typedef struct exec_struc
{
	int		infile;
	int		outfile;
	int		fdin;
	int		fdout;
	int		num_commands;
	int		**pipe_fd;
	int		*fork_id;
	char	*test_cmd[3][3];
}	t_exec;

void	redirection(t_exec *data);
void	*prepare(void);
void	execute(t_exec *data, int fdin, int fdout, int i);
void	close_pipes(t_exec	*data);
void	waitpid_forks(t_exec *data);
void	create_pipes(t_exec *data);
void	*testing(t_exec *data);

void	execution(void)
{
	t_exec	*data;
	int		i;

	data = prepare();
	data = testing(data);
	redirection(data);
	create_pipes(data);
	i = 0;
	while (i < data->num_commands)
	{
		data->fork_id[i] = fork();
		if (data->fork_id[i] == -1)
			exit (1);
		if (i == 0 && data->fork_id[i] == 0)
			execute(data, data->fdin, data->pipe_fd[i][1], i);
		else if (i == data->num_commands - 1 && data->fork_id[i] == 0)
			execute(data, data->pipe_fd[i - 1][0], data->fdout, i);
		else if (data->fork_id[i] == 0)
			execute(data, data->pipe_fd[i - 1][0], data->pipe_fd[i][1], i);
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
	data->num_commands = 3;
	data->infile = 0;
	data->outfile = 1;
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

void	redirection(t_exec *data)
{
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
		data->fdout = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!data->fdout)
			exit(1);
	}
	else
		data->fdout = STDOUT_FILENO;
}

void	execute(t_exec *data, int fdin, int fdout, int i)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		exit (1);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		exit (1);
	close_pipes(data);
	execve(data->test_cmd[i][0], data->test_cmd[i], NULL);
	write (2, "Error execve\n", 8);
	exit(0);
}

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

void	*testing(t_exec *data)
{
	data->test_cmd[0][0] = "/bin/ls";
	data->test_cmd[0][1] = "-la";
	data->test_cmd[0][2] = NULL;
	data->test_cmd[1][0] = "/usr/bin/wc";
	data->test_cmd[1][1] = "-l";
	data->test_cmd[1][2] = NULL;
	data->test_cmd[2][0] = "/bin/cat";
	data->test_cmd[2][1] = NULL;
	return (data);
}
