/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:58:07 by svan-has          #+#    #+#             */
/*   Updated: 2023/01/19 20:36:56 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;
	const char	*src_new;
	char		*temp;	

	if (dest == 0 && src == 0)
		return (NULL);
	temp = dest;
	src_new = src;
	i = 0;
	if (dest > src)
	{
		while (len > 0)
		{
			temp[len - 1] = src_new[len - 1];
			len--;
		}
	}
	else
	{
		while (i++ < len)
			temp[i - 1] = src_new[i - 1];
	}
	return (dest);
}
