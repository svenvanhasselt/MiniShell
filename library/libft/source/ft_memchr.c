/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:39:45 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/25 11:29:16 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_cast;

	s_cast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_cast[i] == (unsigned char)c)
			return ((char *)s + i);
		if ((unsigned char)c == '\0' && s_cast[i + 1] == (unsigned char)c)
			return ((char *)s + i + 1);
		i++;
	}
	return (NULL);
}
