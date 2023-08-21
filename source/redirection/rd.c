/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 15:52:08 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/16 15:29:48 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rd_out(t_node *tokens, t_pl *node)
{
	node->rd_out = true;
	while (tokens && tokens->type == SPC && tokens->type != PIPE && tokens != NULL)
		tokens = tokens->next;
	if (tokens && (tokens->type == WORD || tokens->type == SINGLE_QOUTE || \
	tokens->type == DOUBLE_QOUTE))
	{
		node->file_out = tokens->str;
		close(node->fd_out);
		if (node->rd_out_append == true)
			node->fd_out = open(tokens->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (node->rd_out_append == false)
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

void	rd_in_utils(t_node *tokens, t_pl *node)
{
	node->del_without_nl = tokens->str;
	node->delimiter = ft_strjoin(tokens->str, "\n");
	node->file_in = "here_doc";
}

t_node	*rd_in(t_node *tokens, t_pl *node)
{
	char	*line;

	line = NULL;
	while (tokens && tokens->type == SPC && tokens->type != PIPE && tokens != NULL)
		tokens = tokens->next;
	if (tokens && (tokens->type == WORD || tokens->type == SINGLE_QOUTE || \
	tokens->type == DOUBLE_QOUTE))
	{
		node->file_in = tokens->str;
		close(node->fd_in);
		if (node->rd_in_heredoc == false)
		{
			node->fd_in = open(tokens->str, O_RDONLY);
			printf("this is the file in name = %s\n", tokens->str);
		}
		if (node->rd_in_heredoc == true)
		{
			rd_in_utils(tokens, node);
			rd_heredoc(node);
		}
		if (node->fd_in == -1)
			node->errno_in = errno;
		if (tokens->next != NULL)
			tokens = tokens->next;
	}
	while (tokens && tokens->type == SPC && tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

t_node	*rd_managment(t_node *tokens, t_pl **p_list)
{
	t_pl	*node;

	node = ft_lastlist_lparser(*p_list);
	//printf("in the managment = %s\n", tokens->str);
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
		tokens = rd_in(tokens, node);
	}
	//printf("now\n");
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		while (tokens && tokens->type != PIPE && tokens->next != NULL)
					tokens = tokens->next;
	}
	//printf("now 1\n");
	return (tokens);
}
