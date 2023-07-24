/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/24 13:48:15 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rd_managment_in(t_node *tokens, t_parser_list **p_list)
{
	t_node			*head;
	t_parser_node	*n_list;
	t_parser_list	*node;
	t_node			*first_command;

	head = tokens;
	n_list = NULL;

	while (tokens->type == REDIRECT_IN && tokens->next != NULL)
	{
		tokens = tokens->next;
		while(tokens->type != WORD && tokens->next != NULL)
			tokens = tokens->next;
		if (tokens->type == WORD)
			tokens = tokens->next->next;
		if (tokens->type == WORD)
		{
			first_command = tokens;
			n_list = make_node_parser(tokens);
			printf("the token for parser list = %s\n", (tokens)->str);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			if ((tokens)->next != NULL)
				(tokens) = (tokens)->next;
		}
		// else if ((tokens)->next != NULL)
		// 		(tokens) = (tokens)->next;
	}
	while (head->type == REDIRECT_IN && head != first_command)
	{
		head = head->next;
		while(head->type == SPACE && head->type != PIPE && head != NULL)
		{
			printf("i\n");
			head = head->next;
		}
		//CHECK if I have added this in my syntax error check
		// if (head->type == PIPE)
		// {
		// 	write(2, "syntax error near unexpected token `|'\n", 40);
		// 	exit(3);
		// }
		printf("after the space in rd managment = %s and type = %d\n", head->str, head->type);
		if (head->type == WORD || head->type == SINGLE_QOUTE || head->type == DOUBLE_QOUTE)
		{
			printf("I got here! where are you segfaul!");
			node = ft_lastlist_lparser(*p_list);
			node->rd_in = true;
			node->file_in = head->str;
			close(node->fd_in);
			node->fd_in = open(head->str, O_RDONLY);
			if (node->fd_in == -1)
			{
				node->errno_in = errno;
				printf("this is errno = %d\n", errno);
			}
			if (head->next != NULL)
				head = head->next;
		}
		printf("1 this is the str = \"%s\"\n", head->str);
		while(head->type == SPACE && head->next != NULL)
		{
			printf("i\n");
			head = head->next;
		}
		printf("2 this is the str = \"%s\"\n", head->str);
	}
	return (tokens);
}

t_node	*rd_managment(t_node *tokens, t_parser_list **p_list)
{
	t_parser_list	*node;

	if (tokens->type == REDIRECT_OUT)
	{
		tokens = tokens->next;
		while(tokens->type == SPACE && tokens->type != PIPE && tokens != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
		//CHECK if I have added this in my syntax error check
		// if (tokens->type == PIPE)
		// {
		// 	write(2, "syntax error near unexpected token `|'\n", 40);
		// 	exit(3);
		// }
		printf("after the space? = %s\n", tokens->str);
		if (tokens->type == WORD || tokens->type == SINGLE_QOUTE || tokens->type == DOUBLE_QOUTE)
		{
			node = ft_lastlist_lparser(*p_list);
			node->rd_out = true;
			node->file_out = tokens->str;
			close(node->fd_out);
			node->fd_out = open(tokens->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (node->fd_out == -1)
			{
				node->errno_out = errno;
				printf("this is errno = %d\n", errno);
			}
			if (tokens->next != NULL)
				tokens = tokens->next;
		}
		while(tokens->type == SPACE && tokens->next != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
	}
	else if (tokens->type == REDIRECT_IN)
	{
		tokens = tokens->next;
		while(tokens->type == SPACE && tokens->type != PIPE && tokens != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
		//CHECK if I have added this in my syntax error check
		// if (tokens->type == PIPE)
		// {
		// 	write(2, "syntax error near unexpected token `|'\n", 40);
		// 	exit(3);
		// }
		printf("after the space? = %s\n", tokens->str);
		if (tokens->type == WORD || tokens->type == SINGLE_QOUTE || tokens->type == DOUBLE_QOUTE)
		{
			node = ft_lastlist_lparser(*p_list);
			node->rd_in = true;
			node->file_in = tokens->str;
			close(node->fd_in);
			node->fd_in = open(tokens->str, O_RDONLY);
			if (node->fd_in == -1)
			{
				node->errno_in = errno;
				printf("this is errno = %d\n", errno);
			}
			if (tokens->next != NULL)
				tokens = tokens->next;
		}
		while(tokens->type == SPACE && tokens->next != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
	}
	return(tokens);
}



//I should think about that how I want to impliment the redirection in "<" in my parser