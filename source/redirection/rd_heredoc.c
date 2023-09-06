/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/06 12:36:35 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int g_signals;

char	*join_str_node(t_node *node)
{
	char	*str;

	str = ft_strdup(node->str);
	while (node && node->next)
	{
		str = ft_strjoin_free(str, node->next->str);
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


void	heredoc_without_command(t_node *head, char ***env)
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
	line = get_next_line(1);
	if (!line || \
	ft_strncmp(line, del, ft_strlen(del)) == 0)
	while (1 && g_signals == 0)
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
	if (head->state != IN_DOUBLEQ)
		line = heredoc_make_tokens(line, env);
	if (line && \
	ft_strncmp(line, del, ft_strlen(del)) != 0)
		free(line);
	exit (0);
	waitpid(fork_pid, NULL, 0);
	g_signals = 0;
	signals_parent();
	free(del);
	return ;
}

void	rd_heredoc_utils(t_pl *node, char *line, t_node *lst, char ***env)
{
	t_node	*new;

	new = NULL;
	if (lst->state != IN_DOUBLEQ)
		line = heredoc_make_tokens(line, env);
	if (line && \
	ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) != 0)
	{
		write(node->fd_in, line, ft_strlen(line));
		free(line);
	}
}

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

void	clear_heredoc(t_pl *node, int fork_pid)
{
	int	fork_status;

	if (fork_pid == 0)
		exit (0);
	else
		signals_ignore();
	waitpid(fork_pid, &fork_status, 0);
	g_signals = WEXITSTATUS(fork_status);
	signals_parent();
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}

void	rd_heredoc(t_pl *node, char ***env, t_node *lst)
{
	char	*line;
	int		fork_pid;

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
		rd_heredoc_utils(node, line, lst, env);
	}
	clear_heredoc(node, fork_pid);
}
