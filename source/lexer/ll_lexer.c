/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_lexer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 13:06:30 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/03 14:52:42 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(1);
	node->str = str;
	node->len = len;
	node->type = type;
	node->state = state;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_node	*ft_lastlist(t_node *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back_list(t_node **lst, t_node *new)
{
	t_node	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = ft_lastlist(*lst);
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist(t_node *lst)
{
	int	count;
	t_node	*head;

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

void	free_tokens(t_node **lst)
{
	t_node *temp;

	while (*lst)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}



void	print_list(t_node *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= .%s., state= %u, ", lst->str, lst->state);
		printf("type= %d ,", lst->type);
		lst = lst->next;
	}
	printf("str= .%s., state= %u ", lst->str, lst->state);
	printf("type= %d\n", lst->type);
}
