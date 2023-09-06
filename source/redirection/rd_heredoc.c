/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/06 17:35:54 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str_node(t_node *node)
{
	char	*str;

	//printf("this is node->str = %s\n", (*node)->str);
	str = ft_strdup(node->str);
	while (node && node->next)
	{
		str = ft_strjoin(str, node->next->str);
		node = node->next;
	}
	return (str);
}

char	*heredoc_make_tokens(char *line, char ***env)
{
	t_node	*new;
	new = heredoc_expand_split(line, env);
	free(line);
	line = join_str_node(new);
	free_tokens(new);
	return (line);
}

void	heredoc_without_command(t_node *head)
{
	char	*line;
	char	*del;

	line = NULL;
	del = ft_strjoin(head->str, "\n");
	while (1)
	{
		line = get_next_line(1);
		if (!line || \
		ft_strncmp(line, del, ft_strlen(del)) == 0)
		{
			free(line);
			break ;
		}
		if (line && \
		ft_strncmp(line, del, ft_strlen(del)) != 0)
			free(line);
	}
	free(del);
	return ;
}

void	rd_heredoc_utils(t_pl *node, char *line)
{
	if (line && \
	ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) != 0)
	{
		write(node->fd_in, line, ft_strlen(line));
		free(line);
	}
}

void	rd_heredoc(t_pl *node, char ***env, t_node *lst)
{
	char	*line;

	line = NULL;
	unlink("here_doc");
	close(node->fd_in);
	node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
	while (1)
	{
		line = get_next_line(1);
		if (!line || \
		ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) == 0)
		{
			free(line);
			break ;
		}
		if (lst->state != IN_DOUBLEQ)
			line = heredoc_make_tokens(line, env);
		rd_heredoc_utils(node, line);
	}
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}
