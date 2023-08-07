/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_node_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:17:04 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/02 12:29:59 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_node	*make_node_parser(t_node *token)
{
	t_parser_node	*node;

	// I changed this : 	if (token->type == SPACE)
	//	return (NULL); to the one below and then I commented it! why?
	// if (token != NULL && token->type == SPACE)
	// 	return (NULL);
	node = (t_parser_node *)malloc(sizeof(t_parser_node));
	if (node == NULL)
		exit(1);
	if (token == NULL)
		node->str = NULL;
	else
		node->str = token->str;
	node->next = NULL;
	node->prev = NULL;
	if (token == NULL)
		printf("the str= \"NULL\" and Type = 0\n");
	else
		printf("the str= \"%s\" and Type = %d\n", node->str, token->type);
	//sleep(2);
	return (node);
}

t_parser_node	*ft_lastlist_parser(t_parser_node *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back_list_parser(t_parser_node **lst, t_parser_node *new)
{
	t_parser_node	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = ft_lastlist_parser(*lst);
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist_parser(t_parser_node *lst)
{
	int				count;
	t_parser_node	*node;

	count = 0;
	if (!lst)
		return (0);
	node = lst;
	while (node != NULL)
	{
		node = node->next;
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
		lst = lst->next;
	}
	printf("str= %s\n", lst->str);
}

void	free_list(t_parser_node *lst)
{
	t_parser_node *temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}