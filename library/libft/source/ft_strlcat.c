/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:30:51 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/24 13:53:26 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	x;

	i = ft_strlen(dst);
	x = 0;
	if (i > dstsize || dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (((i + x) < dstsize - 1) && src[x])
	{
		dst[i + x] = src[x];
		x++;
	}
	if (dstsize > 0 && i < dstsize)
		dst[i + x] = '\0';
	return (i + ft_strlen(src));
}
