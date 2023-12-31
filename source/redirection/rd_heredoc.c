/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/07 16:19:23 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	g_signals;

char	*join_str_node(t_node *node)
{
	char	*str;
	t_node	*temp;

	temp = node;
	str = ft_strdup(node->str);
	while (node && node->next)
	{
		str = ft_strjoin_free(str, node->next->str);
		node = node->next;
	}
	free_tokens(temp);
	return (str);
}

char	*heredoc_make_tokens(char *line, char ***env)
{
	t_node	*new;

	new = NULL;
	make_tokens(line, &new);
	heredoc_expansion(&new, env);
	free(line);
	line = join_str_node(new);
	return (line);
}

void	heredoc_without_command(t_node *head)
{
	char	*line;
	char	*del;
	int		fork_pid;

	prep_heredoc_nocom(head, &line, &del, &fork_pid);
	if (g_signals == 2)
		return ;
	while (fork_pid == 0 && g_signals < 2)
	{
		line = get_next_line(1);
		if (!line)
			exit (1);
		if (ft_strncmp(line, del, ft_strlen(del)) == 0)
			exit (0);
		if (line && \
		ft_strncmp(line, del, ft_strlen(del)) != 0)
			free(line);
	}
	clear_heredoc_nocommand(fork_pid, del);
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
	int		fork_pid;
	char	*line;

	prepare_heredoc(node, &line, &fork_pid);
	if (g_signals == 2)
		return ;
	while (fork_pid == 0 && g_signals < 2)
	{
		line = get_next_line(1);
		if (!line)
			exit (1);
		if (ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) == 0)
			exit (0);
		if (lst->state != IN_DOUBLEQ)
			line = heredoc_make_tokens(line, env);
		rd_heredoc_utils(node, line);
	}
	clear_heredoc(node, fork_pid);
}
