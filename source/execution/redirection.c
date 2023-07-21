/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:42:45 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/21 12:43:26 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		redirect(t_parser_list *parser, int fd, bool STDIN)
{
	// int	fd_in;
	int	fd_out;

	if (STDIN == true)
	{
		return (fd);
	}
	else
	{
		if (parser->rd_out)
			fd_out = parser->fd_out;
		else
			return (fd);
		if (parser->rd_out && fd_out < 0)
			error_exit(parser->file_out, parser->errno_out);
		return (fd_out);
	}
	return (-1);
}

void	redirection(t_parser_list *parser, t_exec *data, int i)
{
	if (data->num_commands == 1 && data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, STDIN_FILENO, true);
		data->fdout = redirect(parser, STDOUT_FILENO, false);
	}
	else if (i == 0 && data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, STDIN_FILENO, true);
		data->fdout = redirect(parser, data->pipe_fd[i][1], false);
	}
	else if (i == data->num_commands - 1 && data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, data->pipe_fd[i - 1][0], true);
		data->fdout = redirect(parser, STDOUT_FILENO, false);
	}
	else if (data->fork_pid[i] == 0)
	{
		data->fdin = redirect(parser, data->pipe_fd[i - 1][0], true);
		data->fdout = redirect(parser, data->pipe_fd[i][1], false);
	}
	data->cmd_table = parser->cmd_table;
}