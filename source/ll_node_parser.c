/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:17:04 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/07 11:50:49 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_node	*make_node_parser(t_node **tokens)
{
	t_parser_node	*node;

	node = (t_parser_node *)malloc(sizeof(t_parser_node));
	if (node == NULL)
		exit(1);
	// printf("hi hi\n");
	node->str = (*tokens)->str;
	// node->len = len;
	// printf("hi hi1\n");
	// node->n_type = type;
	// printf("hi hi2\n");
	// node->state = state;
	// printf("hi hi3\n");
	node->nxt_node = NULL;
	node->prev_node = NULL;
	printf("hi hi4\n");
	printf("the str= %s\n", node->str);
	return (node);
}

t_parser_node	*ft_lastlist_parser(t_parser_node *lst)
{
	if (!lst)
		return (0);
	// printf("hi hi9\n");
	while (lst->next)
		lst = lst->next;
	// printf("hi hi10\n");
	return (lst);
}

void	ft_add_back_list_parser(t_parser_node **lst, t_parser_node *new)
{
	t_parser_node	*current;

	if (!new || !lst)
		return ;
	// printf("hi hi5\n");
	if (!*lst)
	{
		// printf("hi hi6\n");
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	// printf("hi hi7\n");
	current = ft_lastlist(*lst);
	// printf("hi hi8\n");
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist_parser(t_parser_node *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	print_list_parser(t_parser_node *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= %s, ", lst->str);
		printf("type= %d ,", lst->n_type);
		lst = lst->next;
	}
	printf("str= %s, ", lst->str);
	printf("type= %d ,", lst->n_type);
}
