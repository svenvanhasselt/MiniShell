/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_list_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 11:55:38 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/30 16:53:02 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	free_llist(t_pl *p_list)
// {
// 	t_pl	*temp;
// 	int		i;

// 	i = 0;
// 	if (!p_list)
// 	{
// 		printf("do I return ? \n");
// 		return ;
// 	}
// 	printf("pointer p_list= %p\n", p_list);
// 	printf("pointer P_list->lst = %p\n", (p_list)->lst);
// 	printf("pointer P_list->next = %p\n", (p_list)->next);
// 	// printf("this = %s\n", (p_list)->lst->str);
// 	printf("this is the parser list in free:\n");
// 	print_list_lparser(&p_list);
// 	printf("make parser thats it\n");
// 	while (p_list)
// 	{
// 		temp = p_list;
// 		// if (p_list->next)
// 		// {
// 		// 	printf("in the if\n");
// 		// 	free_list(temp->lst);
// 		// 	while(temp->cmd_table[i] != NULL)
// 		// 	{
// 		// 		free(temp->cmd_table[i]);
// 		// 		i++;
// 		// 	}
// 		// 	free(temp->cmd_table);
// 		// }
// 		// free_list(p_list->lst);
// 		// if (p_list->next)
// 		// 	free_list(p_list->lst);
// 		p_list = (p_list)->next;
// 		printf("whyyyyy\n");
// 		printf("pointer temp = %p and temp->next = %p\n", temp, temp->next);
// 		// while(temp->cmd_table[i] != NULL)
// 		// {
// 		// 	free(temp->cmd_table[i]);
// 		// 	i++;
// 		// }
// 		// free(temp->cmd_table);
// 		free_list(temp->lst);
// 		// if (temp->next)
// 		// {
// 		// 	printf("in the if\n");
// 		// 	free_list(temp->lst);
// 		// 	while(temp->cmd_table[i] != NULL)
// 		// 	{
// 		// 		free(temp->cmd_table[i]);
// 		// 		i++;
// 		// 	}
// 		// 	free(temp->cmd_table);
// 		// }
// 		// if (temp->lst)
// 		printf("free 1\n");
// 		free(temp->file_in);
// 		printf("free 1.1\n");
// 		free(temp->file_out);
// 		printf("free 1.2\n");
// 		free(temp->delimiter);
// 		printf("free 1.3\n");
// 		free(temp->del_without_nl);
// 		printf("free 2\n");
// 		free(temp);
// 		printf("free 3\n");
// 	}
// 	printf("this is the parser list after free:\n");
// 	print_list_lparser(&p_list);
// 	printf("make parser thats it\n");
// 	p_list = NULL;
// }

void	free_llist(t_pl **p_list)
{
	t_pl	*temp;
	int		i;

	i = 0;
	if (!p_list || !*p_list)
	{
		printf("do I return ? \n");
		return ;
	}
	while (*p_list)
	{
		temp = *p_list;
		// if (p_list->next)
		// {
		// 	printf("in the if\n");
		// 	free_list(temp->lst);
		// 	while(temp->cmd_table[i] != NULL)
		// 	{
		// 		free(temp->cmd_table[i]);
		// 		i++;
		// 	}
		// 	free(temp->cmd_table);
		// }
		// free_list(p_list->lst);
		// if (p_list->next)
		// 	free_list(p_list->lst);
		*p_list = (*p_list)->next;
		i = 0;
		while(temp->cmd_table[i] != NULL)
		{
			free(temp->cmd_table[i]);
			i++;
		}
		free(temp->cmd_table);
		free_list(temp->lst);
		free(temp->file_in);
		free(temp->file_out);
		free(temp->delimiter);
		free(temp->del_without_nl);
		free(temp);
	}
}

void	print_list_lparser(t_pl **plist)
{
	t_pl	*head;

	if (!plist)
		printf("I am empty1  \n");
	if (!*plist)
		printf("I am empty\n");
	if (!plist || !*plist)
		return ;
	head = *plist;
	while (head->next != NULL)
	{
		print_list_parser(head->lst);
		head = head->next;
	}
	print_list_parser(head->lst);
}
