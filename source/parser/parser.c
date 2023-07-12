/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/12 17:16:21 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_parser(t_node **tokens)
{
	t_parser_list *p_list;
	t_parser_node	*n_list;
	// t_parser_list *head;

	p_list = NULL;
	n_list = NULL;
	// head = *tokens;
	if ((*tokens)->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(404);
	}
	while((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL)
		{
			n_list = make_node_parser(*tokens);
			// head = *tokens;
			printf("the token for parser list = %s\n", (*tokens)->str);
			ft_add_back_list_lparser(&p_list, make_node_lparser(n_list));
			(*tokens) = (*tokens)->next;
		}
		else
			break;
		//while((*tokens)->type != PIPE && (*tokens)->type != SPACE && (*tokens) != NULL)
		while((*tokens)->type != PIPE && (*tokens) != NULL)
		{
			if ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			{
				printf("got ya = %s\n", (*tokens)->str);
				printf("this should be the rest of the list = ");
				print_list(*tokens);
				*tokens = rd_managment(*tokens, &p_list);
				printf("I got out of the rd while\n");
			}
			// we have the proplem that if we get a pipe after redirections we can not make a node anymore and it will ruin the parsing
			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			else
				break;
		}
		while (((*tokens)->type == PIPE || (*tokens)->type == SPACE) && (*tokens) != NULL)
			(*tokens) = (*tokens)->next;
		if (*tokens == NULL)
			break;
	}
	printf("I got here\n");
	print_list_lparser(&p_list);
	printf("its finished\n");
}
