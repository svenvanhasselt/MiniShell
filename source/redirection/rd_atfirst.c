/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_atfirst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/23 17:38:02 by psadeghi      ########   odam.nl         */
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

// t_node	*rd_atfirst_in(t_node *tokens, t_node *first_command, t_pl *node)
// {
// 	char *line;

// 	line = NULL;
// 	node->rd_in = true;
// 	tokens = tokens->next;
// 	if (tokens->type == REDIRECT_IN)
// 	{
// 		node->rd_in_heredoc = true;
// 		tokens = tokens->next;
// 	}
// 	while (tokens && tokens->type == SPC && tokens->type != PIPE && tokens != NULL)
// 		tokens = tokens->next;
// 	if (tokens && (tokens->type == WORD || tokens->type == SINGLE_QOUTE || \
// 	tokens->type == DOUBLE_QOUTE) && tokens != first_command)
// 	{
// 		free(node->file_in);
// 		node->file_in = ft_strdup(tokens->str);
// 		close(node->fd_in);
// 		if (node->rd_in_heredoc == false)
// 		{
// 			node->fd_in = open(tokens->str, O_RDONLY);
// 			printf("this is the file in name = %s\n", tokens->str);
// 		}
// 		if (node->rd_in_heredoc == true)
// 		{
// 			rd_in_utils(tokens, node);
// 			rd_heredoc(node);
// 		}
// 		if (node->fd_in == -1)
// 			node->errno_in = errno;
// 		if (tokens->next != NULL)
// 			tokens = tokens->next;
// 	}
// 	while (tokens && tokens->type == SPC && tokens->next != NULL)
// 		tokens = tokens->next;
// 	return (tokens);
// }

void	rd_atfirst_in(t_node *head, t_node *first_command, t_pl *node)
{
	while (head && head->type == REDIRECT_IN && head != first_command)
	{
		head = head->next;
		if (head->type == REDIRECT_IN)
		{
			if (node != NULL)
			{
				printf("I got here and no need for that shit\n");
				node->rd_in_heredoc = true;
			}
			head = head->next;
		}
		while (head->type == SPC && head->type != PIPE && head != NULL)
			head = head->next;
		if (head->type == WORD || head->type == SINGLE_QOUTE || \
		head->type == DOUBLE_QOUTE)
		{
			if (!node && !first_command)
				heredoc_without_command(head);
			else
				rd_atfirst_in_utils(head, node);
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
		{
			printf("this is the tokens->str = %s\n", (*tokens)->str);
			first_command = rd_makelist_utils(*tokens, first_command, p_list);
		}
		if (first_command == NULL)
		{
			n_list = make_node_parser(NULL);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			if ((*tokens)->next != NULL && (*tokens)->type != PIPE)
				(*tokens) = (*tokens)->next;
		}
		// if ((*tokens)->type == WORD)
		// 	(*tokens) = rd_makelist_utils(*tokens, first_command, p_list);
		// else
		// {
		// 	n_list = make_node_parser(NULL);
		// 	ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		// 	if ((*tokens)->next != NULL && (*tokens)->type != PIPE)
		// 		(*tokens) = (*tokens)->next;
		// }
	}
	return (first_command);
}

t_node	*rd_atfirst_managment(t_node *tokens, t_pl **p_list)
{
	t_node	*head;
	t_pl	*node;
	t_node	*first_command;

	head = tokens;
	first_command = rd_makelist(&tokens, p_list, tokens->type);
	printf("I am getting out\n");
	//printf("this is the first_command = %s\n", first_command->str);
	node = ft_lastlist_lparser(*p_list);
	while (tokens && tokens->type == SPC && tokens->next != NULL)
		tokens = tokens->next;
	if (head->type == REDIRECT_IN)
	{
		//rd_atfirst_in(head, first_command, node);
		rd_atfirst_in(head, first_command, node);
	}
	else if (head->type == REDIRECT_OUT)
		rd_atfirst_out(head, first_command, node);
	if (node && (node->fd_in == -1 || node->fd_out == -1))
	{
		while (tokens && tokens->type != PIPE && tokens->next != NULL)
			tokens = tokens->next;
	}
	return (tokens);
}
