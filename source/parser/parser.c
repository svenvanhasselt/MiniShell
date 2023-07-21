/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/21 11:14:00 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_parser(t_node **tokens, t_parser_list **p_list)
{
	t_parser_list *last;
	t_parser_node	*n_list;
	t_node	*head;

	n_list = NULL;
	last = NULL;
	
	syntax_error(*tokens);
	printf("first token = %s\n", (*tokens)->str);
	head = *tokens;
	while((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL)
		{
			n_list = make_node_parser(*tokens);
			printf("the token for parser list = %s\n", (*tokens)->str);
			ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
			last = ft_lastlist_lparser(*p_list);
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
		}
		else
		{
			if ((head)->next == NULL && ft_sizelist(head) == 1)
			{
				n_list = make_node_parser(head);
				printf("if only one --> the token for parser list = %s\n", head->str);
				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
				last = ft_lastlist_lparser(*p_list);
				break;
			}
			else
				break;
		}
		while((*tokens)->type != PIPE && (*tokens) != NULL)
		{
			while ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			{
				printf("got ya = %s\n", (*tokens)->str);
				printf("this should be the rest of the list = ");
				print_list(*tokens);
				*tokens = rd_managment(*tokens, p_list);
				if ((*tokens)->type == PIPE || (*tokens)->next == NULL)
					break;
				printf("I got out of the rd while\n");
			}
			if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && last->rd_out == true))
				break;
			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			else
				break;
		}
		while (((*tokens)->type == PIPE || (*tokens)->type == SPACE) && (*tokens) != NULL)
		{
			(*tokens) = (*tokens)->next;
			head = (*tokens);
		}
		if (*tokens == NULL)
			break;
	}
	printf("I got here\n");
	print_list_lparser(p_list);
	printf("its finished\n");
}


//fd leaks
//check syntax error at first

// I should take care of redirection in!