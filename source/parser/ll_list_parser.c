/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_list_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 11:55:38 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/13 10:59:29 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signals;

t_pl	*make_node_lparser(t_pn *small_list)
{
	t_pl	*node;

	node = (t_pl *)malloc(sizeof(t_pl));
	if (node == NULL)
		exit(1);
	node->lst = small_list;
	node->next = NULL;
	node->rd_in = false;
	node->fd_in = -5;
	node->errno_out = 0;
	node->rd_out = false;
	node->fd_out = -5;
	node->file_out = NULL;
	node->file_in = NULL;
	node->errno_out = 0;
	node->rd_out_append = false;
	node->rd_in_heredoc = false;
	node->del_without_nl = NULL;
	node->delimiter = NULL;
	return (node);
}

t_pl	*ft_lastlist_lparser(t_pl *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back_list_lparser(t_pl **lst, t_pl *new)
{
	t_pl	*current;

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

int	ft_sizelist_lparser(t_pl *lst)
{
	int		count;
	t_pl	*head;

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

void	free_llist(t_pl **p_list)
{
	t_pl	*temp;
	int		i;

	if (!p_list || !*p_list)
		return ;
	while (*p_list)
	{
		temp = *p_list;
		*p_list = (*p_list)->next;
		if (g_signals < 2)
		{
			i = -1;
			while (temp->cmd_table[++i] != NULL)
				free(temp->cmd_table[i]);
			free(temp->cmd_table);
		}
		free_list(temp->lst);
		close_fd(temp->fd_in, temp->fd_out);
		free(temp->file_in);
		free(temp->file_out);
		free(temp->delimiter);
		free(temp->del_without_nl);
		free(temp);
	}
}

// void	print_list_lparser(t_pl **plist)
// {
// 	t_pl	*head;

// 	if (!plist || !*plist)
// 		return ;
// 	head = *plist;
// 	while (head->next != NULL)
// 	{
// 		print_list_parser(head->lst);
// 		head = head->next;
// 	}
// 	print_list_parser(head->lst);
// }