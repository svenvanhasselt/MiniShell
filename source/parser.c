/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/11 13:48:09 by psadeghi      ########   odam.nl         */
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
	while((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL)
		{
			n_list = make_node_parser(*tokens);
			printf("the token for parser list = %s\n", (*tokens)->str);
			ft_add_back_list_lparser(&p_list, make_node_lparser(n_list));
			(*tokens) = (*tokens)->next;
		}
		else
			break;
		//while((*tokens)->type != PIPE && (*tokens)->type != SPACE && (*tokens) != NULL)
		while((*tokens)->type != PIPE && (*tokens) != NULL)
		{
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
