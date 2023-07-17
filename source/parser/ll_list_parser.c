/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_list_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 11:55:38 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/17 18:17:40 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_list	*make_node_lparser(t_parser_node *small_list)
{
	t_parser_list	*node;

	node = (t_parser_list *)malloc(sizeof(t_parser_list));
	if (node == NULL)
		exit(1);
	node->lst = small_list;
	node->next = NULL;
	node->rd_in = false;
	node->fd_in = -5;
	node->file_in = NULL;
	node->errno_out = 0;
	node->rd_out = false;
	node->fd_out = -5;
	node->file_out = NULL;
	node->errno_out = 0;
	return (node);
}

t_parser_list	*ft_lastlist_lparser(t_parser_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back_list_lparser(t_parser_list **lst, t_parser_list *new)
{
	t_parser_list	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = ft_lastlist_lparser(*lst);
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

void	print_list_lparser(t_parser_list **plist)
{
	if (!plist || !*plist)
	{
		printf("it is NULL\n");
		return ;
	}
	while ((*plist)->next != NULL)
	{
		printf("the head each node = \"%s\"\n", (*plist)->lst->str);
		print_list_parser((*plist)->lst);
		*plist = (*plist)->next;
	}
	printf("the head each node = \"%s\"\n", (*plist)->lst->str);
	print_list_parser((*plist)->lst);
}

void	free_llist(t_parser_list **p_list)
{
	t_parser_list *temp;

	if (!p_list || !*p_list)
	{
		printf("it is NULL\n");
		return ;
	}
	while ((*p_list))
	{
		temp = *p_list;
		free_list((*p_list)->lst);
		(*p_list) = (*p_list)->next;
		free(temp);
	}
	printf("done freeing\n");
}
