/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:17:04 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/06 18:12:42 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_node	*make_node(t_node **lst)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(1);
	// printf("hi hi\n");
	node->str = str;
	node->len = len;
	// printf("hi hi1\n");
	node->type = type;
	// printf("hi hi2\n");
	node->state = state;
	// printf("hi hi3\n");
	node->next = NULL;
	node->prev = NULL;
	// printf("hi hi4\n");
	return (node);
}

t_node	*ft_lastlist(t_node *lst)
{
	if (!lst)
		return (0);
	// printf("hi hi9\n");
	while (lst->next)
		lst = lst->next;
	// printf("hi hi10\n");
	return (lst);
}

void	ft_add_back_list(t_node **lst, t_node *new)
{
	t_node	*current;

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

int	ft_sizelist(t_node *lst)
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

void	print_list(t_node *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= %s, state= %u, ", lst->str, lst->state);
		printf("type= %d ,", lst->type);
		lst = lst->next;
	}
	printf("str= %s, state= %u ", lst->str, lst->state);
	printf("type= %d\n", lst->type);
}
