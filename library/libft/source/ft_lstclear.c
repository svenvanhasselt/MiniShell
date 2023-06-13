/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:59:46 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/26 11:24:54 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*del_node;
	t_list	*temp;

	del_node = *lst;
	while (del_node != NULL)
	{
		temp = del_node->next;
		del(del_node->content);
		free(del_node);
		del_node = temp;
	}
	*lst = NULL;
}
