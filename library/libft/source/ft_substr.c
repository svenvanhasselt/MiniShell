/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:21:51 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/22 19:33:54 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calcmalloc(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		i++;
		start++;
	}
	return (i + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substring;
	unsigned int		i;

	substring = (char *) malloc (calcmalloc(s, start, len) * sizeof(char));
	if (!s || substring == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}
