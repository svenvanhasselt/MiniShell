/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/10 17:49:48 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_parser(t_node **tokens)
{
	t_parser_list *p_list;
	t_parser_node	*n_list;
	t_node *head;

	p_list = NULL;
	n_list = NULL;
	head = *tokens;
	if (head->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(404);
	}
	while((*tokens)->next != NULL)
	{
		// printf("pointers %p\n", (*tokens)->next);
		if ((*tokens)->type == SPACE || (*tokens)->type == PIPE)
			(*tokens) = (*tokens)->next;
		// printf("yoho\n");
		n_list = make_node_parser(*tokens);
		// printf("hello I am here\n");
		ft_add_back_list_lparser(&p_list, make_node_lparser(n_list));
		// printf("hello I am here 1\n");
		(*tokens) = (*tokens)->next;
		// printf("hello I am here 2\n");
		while((*tokens)->type == PIPE && (*tokens)->type == SPACE && (*tokens)->next != NULL)
		{
			// printf("hello I am here 3\n");
			// if ((*tokens)->type == SPACE)
			// 	(*tokens) = (*tokens)->next;
			// printf("hello I am here 4\n");
			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
			// printf("hello I am here 5\n");
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
		}
		// printf("hello I am here 6\n");
		if ((*tokens)->next != NULL || (*tokens)->type == PIPE || (*tokens)->type == SPACE)
			(*tokens) = (*tokens)->next;
		else
			break;
		// printf("hello I am here 7\n");
	}
	printf("I got here\n");
}
