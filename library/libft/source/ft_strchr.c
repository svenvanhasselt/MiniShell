/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:32:48 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/22 19:42:01 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		if ((char)c == '\0' && str[i + 1] == '\0')
			return ((char *)str + i + 1);
		i++;
	}
	return (NULL);
}
