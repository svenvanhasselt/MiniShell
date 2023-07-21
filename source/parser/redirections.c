/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/21 13:15:25 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_node	*rd_managment_in(t_node *tokens, t_parser_list **p_list)
// {
	
// }

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