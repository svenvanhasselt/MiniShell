/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/01 20:37:41 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_heredoc;

void	heredoc_without_command(t_node *head)
{
	char	*line;
	char	*del;
	int		fork_pid;

	line = NULL;
	del = ft_strjoin(head->str, "\n");
	signals_heredoc();
	fork_pid = fork();
	if (fork_pid == -1)
		error_exit("operation failure", errno);
	if (fork_pid == 0)
	{
		while (1 && g_heredoc == 0)
		{
			line = get_next_line(1);
			if (line && \
			ft_strncmp(line, del, ft_strlen(del)) != 0)
				free(line);
			if (!line || \
			ft_strncmp(line, del, ft_strlen(del)) == 0)
			{
				free(line);
				break ;
			}
		}
		exit (0);
	}
	waitpid(fork_pid, NULL, 0);
	g_heredoc = 0;
	signals_parent();
	free(del);
	return ;
}

void	rd_heredoc(t_pl *node)
{
	char	*line;
	int		fork_pid;

	line = NULL;
	unlink("here_doc");
	close(node->fd_in);
	node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
	signals_heredoc();
	fork_pid = fork();
	if (fork_pid == -1)
		error_exit("operation failure", errno);
	if (fork_pid == 0)
	{
		while (1 && g_heredoc == 0)
		{
			line = get_next_line(1);
			if (line && \
			ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) != 0)
			{
				write(node->fd_in, line, ft_strlen(line));
				free(line);
			}
			if (!line || \
			ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) == 0)
				break ;
		}
		exit (0);
	}
	waitpid(fork_pid, NULL, 0);
	signals_parent();
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}
