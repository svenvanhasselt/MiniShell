/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/06 12:33:58 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/07 17:41:02 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	g_signals;

void	prepare_heredoc(t_pl *node, char **line, int *fork_pid)
{
	line = NULL;
	unlink("here_doc");
	close(node->fd_in);
	node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
	signals_heredoc();
	*fork_pid = fork();
	if (*fork_pid == -1)
		error_exit("operation failure", errno);
}

void	prep_heredoc_nocom(t_node *head, char **line, char **del, int *fork_pid)
{
	line = NULL;
	*del = ft_strjoin(head->str, "\n");
	signals_heredoc();
	*fork_pid = fork();
	if (*fork_pid == -1)
		error_exit("operation failure", errno);
}

void	clear_heredoc_nocommand(int fork_pid, char *del)
{
	int	fork_status;

	if (fork_pid == 0)
		exit (0);
	else
		signals_ignore();
	waitpid(fork_pid, &fork_status, 0);
	g_signals = WEXITSTATUS(fork_status);
	signals_parent();
	free(del);
}

void	clear_heredoc(t_pl *node, int fork_pid)
{
	int	fork_status;

	if (fork_pid == 0)
		exit (0);
	signals_ignore();
	waitpid(fork_pid, &fork_status, 0);
	g_signals = WEXITSTATUS(fork_status);
	signals_parent();
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}
