/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_list_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:55:38 by psadeghi          #+#    #+#             */
/*   Updated: 2023/07/27 13:27:50 by sven             ###   ########.fr       */
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
	t_parser_list *head;

	count = 0;
	if (!lst)
		return (0);
	head = lst;
	while (head != NULL)
	{
		head = head->next;
		count++;
	}
	return (count);
}

void	print_list_lparser(t_parser_list **plist)
{
	t_parser_list	*head;

	if (!plist || !*plist)
	{
		printf("it is NULL1\n");
		return ;
	}
	head = *plist;
	while (head->next != NULL)
	{
		printf("the head each node = \"%s\"\n", head->lst->str);
		print_list_parser(head->lst);
		head = head->next;
	}
	printf("the head each node = \"%s\"\n", head->lst->str);
	print_list_parser(head->lst);
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
