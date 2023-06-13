/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:14:16 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/19 17:25:20 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		x = 0;
		while (haystack[i + x] == needle[x] && i + x < len)
		{
			if (x == ft_strlen(needle) - 1)
			{
				return ((char *)haystack + i);
			}
			x++;
		}
		i++;
	}
	return (NULL);
}
