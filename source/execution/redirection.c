/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:42:45 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/14 14:14:41 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirect_in(t_pl *parser, int *status, int fd)
{
	if (parser->rd_in || parser->rd_in_heredoc)
		fd = parser->fd_in;
	else
		return (fd);
	if (parser->rd_in && fd < 0)
	{
		error_seterrno(parser->file_in, NULL, parser->errno_in);
		*status = 1;
		return (-1);
	}
	return (fd);
}

int	redirect_out(t_pl *parser, int *status, int fd)
{
	if (parser->rd_out || parser->rd_out_append)
		fd = parser->fd_out;
	else
		return (fd);
	if (parser->rd_out && fd < 0)
	{
		error_seterrno(parser->file_out, NULL, parser->errno_out);
		*status = 1;
		return (-1);
	}
	return (fd);
}

int	redirect(t_pl *parser, int *status, int fd, bool STDIN)
{
	if (STDIN == true)
		return (redirect_in(parser, status, fd));
	else
		return (redirect_out(parser, status, fd));
	return (-1);
}

void	redirection(t_pl *parser, t_exec *data, int i)
{
	int	*status;

	status = &data->exit_status;
	if ((data->num_commands == 1 && data->fork_pid[i] == 0))
	{
		data->fdin = redirect(parser, status, STDIN_FILENO, true);
		data->fdout = redirect(parser, status, STDOUT_FILENO, false);
	}
	else if (i == 0 && data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, status, STDIN_FILENO, true);
		data->fdout = redirect(parser, status, data->pipe_fd[i][1], false);
	}
	else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, status, data->pipe_fd[i - 1][0], true);
		data->fdout = redirect(parser, status, STDOUT_FILENO, false);
	}
	else if (data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, status, data->pipe_fd[i - 1][0], true);
		data->fdout = redirect(parser, status, data->pipe_fd[i][1], false);
	}
	data->cmd_table = parser->cmd_table;
}
