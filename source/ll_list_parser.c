/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_list_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 11:55:38 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/10 16:32:06 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_list	*make_node_lparser(t_parser_node *small_list)
{
	t_parser_list	*node;

	node = (t_parser_list *)malloc(sizeof(t_parser_list));
	if (node == NULL)
		exit(1);
	// printf("hi hi\n");
	node->lst = small_list;
	// node->len = len;
	// printf("hi hi1\n");
	// node->n_type = type;
	// printf("hi hi2\n");
	// node->state = state;
	// printf("hi hi3\n");
	node->next = NULL;
	// node->next->next = NULL;
	// node->prev_node = NULL;
	// printf("hi hi4\n");
	// printf("the str= %s\n", node->str);
	return (node);
}

t_parser_list	*ft_lastlist_lparser(t_parser_list *lst)
{
	if (!lst)
		return (0);
	// printf("hi hi9\n");
	while (lst->next)
	{
		printf("Hi\n");
		printf("%p\n", lst->next);
		lst = lst->next;
		if (lst == NULL)
		{
			printf("NULL\n");
		}
	}
	printf("hi hi10\n");
	return (lst);
}

void	ft_add_back_list_lparser(t_parser_list **lst, t_parser_list *new)
{
	t_parser_list	*current;

	if (!new || !lst)
		return ;
	// printf("hi hi5\n");
	if (!*lst)
	{
		// printf("hi hi6\n");
		printf("first time\n");
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	// printf("hi hi7\n");
	current = ft_lastlist_lparser(*lst);
	// printf("hi hi8\n");
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist_lparser(t_parser_list *lst)
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

void	print_list_lparser(t_parser_list *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		// printf("str= %s, ", lst->str);
		// printf("type= %d ,", lst->n_type);
		lst = lst->next;
	}
	// printf("str= %s, ", lst->str);
	// printf("type= %d ,", lst->n_type);
}
