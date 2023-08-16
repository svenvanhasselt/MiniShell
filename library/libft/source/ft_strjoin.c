/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 18:10:58 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/16 17:05:41 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s1_s2;
	int		i;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	s1_s2 = (char *) malloc ((len + 1) * sizeof(char));
	if (s1_s2 == NULL)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		s1_s2[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		s1_s2[i] = *s2;
		i++;
		s2++;
	}
	s1_s2[i] = '\0';
	return (s1_s2);
}
