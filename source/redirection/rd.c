/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 15:52:08 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/11 11:56:03 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signals;

t_node	*rd_out(t_node *tokens, t_pl *node)
{
	node->rd_out = true;
	while (tokens && tokens->type == SPC && \
	tokens->type != PIPE && tokens != NULL)
		tokens = tokens->next;
	if (tokens && (tokens->type == WORD || \
	tokens->type == SINGLE_QOUTE || tokens->type == DOUBLE_QOUTE))
	{
		free(node->file_out);
		node->file_out = ft_strdup(tokens->str);
		close(node->fd_out);
		if (node->rd_out_append == true && g_signals != 2)
			node->fd_out = open(tokens->str, O_CREAT | \
			O_WRONLY | O_APPEND, 0644);
		if (node->rd_out_append == false && g_signals != 2)
			node->fd_out = open(tokens->str, O_CREAT | \
			O_WRONLY | O_TRUNC, 0644);
		if (node->fd_out == -1)
			node->errno_out = errno;
		if (tokens->next != NULL)
			tokens = tokens->next;
	}
	while (tokens && tokens->type == SPC && tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

void	rd_in_utils(t_node *tokens, t_pl *node, char ***env)
{
	free(node->del_without_nl);
	node->del_without_nl = ft_strdup(tokens->str);
	free(node->delimiter);
	node->delimiter = ft_strjoin(tokens->str, "\n");
	free(node->file_in);
	node->file_in = ft_strdup("here_doc");
	rd_heredoc(node, env, tokens);
}

t_node	*rd_in(t_node *tokens, t_pl *node, char ***env)
{
	while (tokens && tokens->type == SPC && \
	tokens->type != PIPE && tokens != NULL)
		tokens = tokens->next;
	if (tokens && (tokens->type == WORD || tokens->type == SINGLE_QOUTE || \
	tokens->type == DOUBLE_QOUTE))
	{
		free(node->file_in);
		node->file_in = ft_strdup(tokens->str);
		close(node->fd_in);
		if (node->rd_in_heredoc == false)
			node->fd_in = open(tokens->str, O_RDONLY);
		if (node->rd_in_heredoc == true)
			rd_in_utils(tokens, node, env);
		if (node->fd_in == -1)
			node->errno_in = errno;
		if (tokens->next != NULL)
			tokens = tokens->next;
	}
	while (tokens && tokens->type == SPC && tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

t_node	*rd_managment_utils(t_node *tokens, t_pl *node, char ***env)
{
	if (tokens->type == REDIRECT_OUT)
	{
		tokens = tokens->next;
		if (tokens->type == REDIRECT_OUT)
		{
			node->rd_out_append = true;
			tokens = tokens->next;
		}
		tokens = rd_out(tokens, node);
	}
	else if (tokens->type == REDIRECT_IN)
	{
		node->rd_in = true;
		tokens = tokens->next;
		if (tokens->type == REDIRECT_IN)
		{
			node->rd_in_heredoc = true;
			tokens = tokens->next;
		}
		tokens = rd_in(tokens, node, env);
	}
	return (tokens);
}

t_node	*rd_managment(t_node *tokens, t_pl **p_list, char ***env)
{
	t_pl	*node;

	node = ft_lastlist_lparser(*p_list);
	tokens = rd_managment_utils(tokens, node, env);
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		while (tokens && tokens->type != PIPE && tokens->next != NULL)
			tokens = tokens->next;
	}
	return (tokens);
}
