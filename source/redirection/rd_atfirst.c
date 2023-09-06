/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_atfirst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/06 15:41:23 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rd_atfirst_out(t_node *head, t_node *first_command, t_pl *node)
{
	while (head->type == REDIRECT_OUT && head != first_command)
	{
		head = head->next;
		if (head->type == REDIRECT_OUT)
		{
			node->rd_out_append = true;
			head = head->next;
		}
		while (head->type == SPC && head->type != PIPE && head != NULL)
			head = head->next;
		if (head->type == WORD || head->type == SINGLE_QOUTE || \
		head->type == DOUBLE_QOUTE)
		{
			rd_atfirst_out_utils(head, node);
			if (head->next != NULL)
				head = head->next;
		}
		while (head->type == SPC && head->next != NULL)
			head = head->next;
	}
}

void	rd_atfirst_in(t_node *head, t_node *f_cmnd, t_pl *node, char ***env)
{
	while (head && head->type == REDIRECT_IN && head != f_cmnd)
	{
		head = head->next;
		if (head->type == REDIRECT_IN)
		{
			if (node != NULL)
				node->rd_in_heredoc = true;
			head = head->next;
		}
		while (head->type == SPC && head->type != PIPE && head != NULL)
			head = head->next;
		if (head->type == WORD || head->type == SINGLE_QOUTE || \
		head->type == DOUBLE_QOUTE)
		{
			if (!node && !f_cmnd)
				heredoc_without_command(head);
			else
				rd_atfirst_in_utils(head, node, env);
			if (head->next != NULL)
				head = head->next;
		}
		while (head->type == SPC && head->next != NULL)
			head = head->next;
	}
}

t_node	*rd_makelist(t_node **tokens, t_pl **p_list, enum e_token rd_type)
{
	t_pn	*n_list;
	t_node	*first_command;

	n_list = NULL;
	first_command = NULL;
	while ((*tokens) && (*tokens)->type == rd_type && (*tokens)->next != NULL)
	{
		(*tokens) = (*tokens)->next;
		if ((*tokens)->type == rd_type)
			(*tokens) = (*tokens)->next;
		while ((*tokens)->type != WORD && (*tokens)->next != NULL)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->type == WORD)
			first_command = rd_ml_utils(*tokens, first_command, p_list);
		if (first_command == NULL)
		{
			n_list = make_node_parser(NULL);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			if ((*tokens)->next != NULL && (*tokens)->type != PIPE)
				(*tokens) = (*tokens)->next;
		}
	}
	return (first_command);
}

t_node	*rd_atfirst_managment(t_node *tokens, t_pl **p_list, char ***env)
{
	t_node	*head;
	t_pl	*node;
	t_node	*first_command;

	head = tokens;
	first_command = rd_makelist(&tokens, p_list, tokens->type);
	node = ft_lastlist_lparser(*p_list);
	if (head->type == REDIRECT_IN)
		rd_atfirst_in(head, first_command, node, env);
	else if (head->type == REDIRECT_OUT)
		rd_atfirst_out(head, first_command, node);
	if (first_command != NULL)
		first_command = first_command->next;
	return (first_command);
}
