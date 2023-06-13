/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:08:53 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/25 14:57:13 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head_node;

	head_node = (t_list *) malloc (sizeof(t_list));
	if (head_node == NULL)
		return (NULL);
	head_node->content = content;
	head_node->next = NULL;
	return (head_node);
}
