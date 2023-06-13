/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:28:39 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/25 10:41:39 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	x;
	char	*src1;
	char	*dest1;

	if (dest == 0 && src == 0)
		return (NULL);
	x = 0;
	src1 = (char *)src;
	dest1 = (char *)dest;
	while (x < n)
	{
		dest1[x] = src1[x];
		x++;
	}
	return (dest);
}
