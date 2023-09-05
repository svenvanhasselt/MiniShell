/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_atfirst_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 17:57:44 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/05 10:31:04 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rd_atfirst_out_utils(t_node *head, t_pl *node)
{
	node->rd_out = true;
	free(node->file_out);
	node->file_out = ft_strdup(head->str);
	close(node->fd_out);
	if (node->rd_out_append == true)
		node->fd_out = open(head->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->rd_out_append == false)
		node->fd_out = open(head->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
		node->errno_in = errno;
}

void	rd_atfirst_in_utils(t_node *head, t_pl *node, char ***env)
{
	char	*line;

	line = NULL;
	node->rd_in = true;
	close(node->fd_in);
	if (node->rd_in_heredoc == false)
	{
		free(node->file_in);
		node->file_in = ft_strdup(head->str);
	}
	if (node->rd_in_heredoc == true)
	{
		free(node->del_without_nl);
		node->del_without_nl = ft_strdup(head->str);
		free(node->delimiter);
		node->delimiter = ft_strjoin(head->str, "\n");
		free(node->file_in);
		node->file_in = ft_strdup("here_doc");
		rd_heredoc(node, env, head);
	}
	else if (node->rd_in_heredoc == false)
		node->fd_in = open(head->str, O_RDONLY);
	if (node->fd_in == -1)
		node->errno_in = errno;
}

t_node	*rd_makelist_utils2(t_node *t, t_node *f_cmnd, t_pl **p_list, char *ar)
{
	t_pn	*n_list;

	n_list = NULL;
	while (t && t->type == SPC)
		t = t->next;
	if (t->type == WORD && \
	ft_strncmp(t->str, ar, ft_strlen(ar)) != 0)
	{
		f_cmnd = t;
		n_list = make_node_parser(t);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
	}
	return (f_cmnd);
}

t_node	*rd_ml_utils(t_node *tokens, t_node *first_command, t_pl **p_list)
{
	char	*after_rd;

	after_rd = NULL;
	after_rd = tokens->str;
	if (tokens->next != NULL)
		tokens = tokens->next;
	while (tokens && tokens->type == SPC)
		tokens = tokens->next;
	while (tokens && (tokens->type == REDIRECT_IN || \
	tokens->type == REDIRECT_OUT))
	{
		while (tokens && tokens->type != PIPE && tokens->type != WORD)
			tokens = tokens->next;
		if (tokens && tokens->type == WORD)
		{
			after_rd = tokens->str;
			if (tokens->next != NULL)
				tokens = tokens->next;
		}
		if (tokens && tokens->type == PIPE)
			return (NULL);
	}
	first_command = rd_makelist_utils2(tokens, first_command, p_list, after_rd);
	return (first_command);
}
