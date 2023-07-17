/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/17 17:51:28 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_parser(t_node **tokens)
{
	t_parser_list *p_list;
	t_parser_list *last;
	t_parser_node	*n_list;
	// t_parser_list *head;

	p_list = NULL;
	n_list = NULL;
	last = NULL;
	// head = *tokens;
	
	// if ((*tokens)->type == PIPE)
	// {
	// 	write(2, "syntax error near unexpected token `|'\n", 40);
	// 	exit(404);
	// }
	syntax_error(*tokens);
	printf("first token = %s\n", (*tokens)->str);
	while((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL)
		{
			n_list = make_node_parser(*tokens);
			// head = *tokens;
			printf("the token for parser list = %s\n", (*tokens)->str);
			ft_add_back_list_lparser(&p_list, make_node_lparser(n_list));
			last = ft_lastlist_lparser(p_list);
			(*tokens) = (*tokens)->next;
		}
		else
			break;
		//while((*tokens)->type != PIPE && (*tokens)->type != SPACE && (*tokens) != NULL)
		while((*tokens)->type != PIPE && (*tokens) != NULL)
		{
			while ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			{
				printf("got ya = %s\n", (*tokens)->str);
				printf("this should be the rest of the list = ");
				print_list(*tokens);
				*tokens = rd_managment(*tokens, &p_list);
				if ((*tokens)->type == PIPE || (*tokens)->next == NULL)
					break;
				printf("I got out of the rd while\n");
			}
			if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && last->rd_out == true))
				break;
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


//fd leaks
//check syntax error at first
// I need to add p_list to ft_readline function so that I can free them each time