/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/23 17:20:06 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rd_heredoc(t_pl *node)
{
	char	*line;

	line = NULL;
	unlink("here_doc");
	node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
	while (1)
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
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}
