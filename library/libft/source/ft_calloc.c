/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:30:06 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/20 17:38:49 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*return_value;

	return_value = malloc(nitems * size);
	if (return_value == NULL)
		return (NULL);
	ft_bzero(return_value, nitems * size);
	return (return_value);
}
