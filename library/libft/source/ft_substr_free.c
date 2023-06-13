/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 18:50:38 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/07 10:36:49 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len, int f)
{
	char				*substring;
	unsigned int		i;
	unsigned int		s_len;

	s_len = ft_strlen(s);
	i = 0;
	while (i < len && i + start < s_len)
		i++;
	substring = (char *) malloc ((i + 1) * sizeof(char));
	if (!s || !substring)
		return (free(s), free(substring), NULL);
	i = -1;
	while (++i < len && s[i + start])
		substring[i] = s[i + start];
	substring[i] = '\0';
	if (f == 1)
		free(s);
	return (substring);
}
