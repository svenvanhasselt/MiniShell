/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:23:08 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/19 17:19:05 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	x;
	char	*str2;

	str2 = (char *)str;
	x = 0;
	while (x < n)
	{
		str2[x] = c;
		x++;
	}
	return (str);
}
