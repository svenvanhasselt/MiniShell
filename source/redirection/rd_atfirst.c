/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_atfirst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/09 20:05:45 by psadeghi      ########   odam.nl         */
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
		while(head->type == SPACE && head->type != PIPE && head != NULL)
			head = head->next;
		if (head->type == WORD || head->type == SINGLE_QOUTE || head->type == DOUBLE_QOUTE)
		{
			node->rd_out = true;
			node->file_out = head->str;
			close(node->fd_out);
			if (node->rd_out_append == true)
				node->fd_out = open(head->str, O_CREAT | O_WRONLY, 0644);
			if (node->rd_out_append == false)
				node->fd_out = open(head->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (node->fd_out == -1)
				node->errno_in = errno;
			if (head->next != NULL)
				head = head->next;
		}
		while(head->type == SPACE && head->next != NULL)
			head = head->next;
	}
}

void	rd_atfirst_in(t_node *head, t_node *first_command, t_pl *node)
{
	while (head->type == REDIRECT_IN && head != first_command)
	{
		head = head->next;
		if (head->type == REDIRECT_IN)
		{
			node->rd_in_heredoc = true;
			head = head->next;
		}
		while(head->type == SPACE && head->type != PIPE && head != NULL)
			head = head->next;
		if (head->type == WORD || head->type == SINGLE_QOUTE || head->type == DOUBLE_QOUTE)
		{
			node->rd_in = true;
			if (node->rd_in_heredoc == false)
				node->file_in = head->str;
			if (node->rd_in_heredoc == true)
			{
				node->del_without_nl = head->str;
				node->delimiter = ft_strjoin(head->str, "\n");
				node->file_in = "here_doc";
			}
			close(node->fd_in);
			if (node->rd_in_heredoc == true)
				node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
			else if (node->rd_in_heredoc == false)
				node->fd_in = open(head->str, O_RDONLY);
			if (node->fd_in == -1)
				node->errno_in = errno;
			if (head->next != NULL)
				head = head->next;
		}
		while(head->type == SPACE && head->next != NULL)
			head = head->next;
	}
}

t_node	*rd_makelist(t_node **tokens, t_pl **p_list, enum e_token rd_type)
{
	t_pn	*n_list;
	t_node	*first_command;
	char	*after_rd;

	n_list = NULL;
	after_rd = NULL;
	first_command = NULL;

	while ((*tokens)->type == rd_type && (*tokens)->next != NULL)
	{
		(*tokens) = (*tokens)->next;
		if ((*tokens)->type == rd_type)
			(*tokens) = (*tokens)->next;
		printf("I got here! 2\n");
		while((*tokens)->type != WORD && (*tokens)->next != NULL)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->type == WORD)
		{
			after_rd = (*tokens)->str;
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
		}
		printf("I got here! 3\n");
		if ((*tokens)->type == WORD && ft_strncmp((*tokens)->str, after_rd, ft_strlen(after_rd)) != 0)
		{
			printf("I got here!\n");
			first_command = (*tokens);
			n_list = make_node_parser((*tokens));
			printf("1 the token for parser list = %s\n", ((*tokens))->str);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			if (((*tokens))->next != NULL)
				((*tokens)) = ((*tokens))->next;
		}
		else
		{
			printf("I get into the else!\n");
			n_list = make_node_parser(NULL);
			printf("2 the token for parser list = %s\n", ((*tokens))->str);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			if (((*tokens))->next != NULL && (*tokens)->type != PIPE)
				((*tokens)) = ((*tokens))->next;
		}
	}
	printf("(*tokens)->str in make list + %s\n", (*tokens)->str);
	return (first_command);
}

t_node	*rd_atfirst_managment(t_node *tokens, t_pl **p_list)
{
	t_node			*head;
	t_pl			*node;
	t_node			*first_command;

	head = tokens;
	printf("I got here! 1\n");
	first_command = rd_makelist(&tokens, p_list, tokens->type);
	node = ft_lastlist_lparser(*p_list);
	if (head->type == REDIRECT_IN)
	{
		rd_atfirst_in(head, first_command, node);
	}
	else if (head->type == REDIRECT_OUT)
	{
		rd_atfirst_out(head, first_command, node);
	}
	printf("this is the string in the managment in %s\n", tokens->str);
	return (tokens);
}
