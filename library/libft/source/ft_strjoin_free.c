/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/22 18:50:38 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/07 10:36:37 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s1_s2;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *) malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	s1_s2 = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1_s2 || !s2)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		s1_s2[i] = s1[i];
	while (s2[j])
		s1_s2[i++] = s2[j++];
	s1_s2[i] = '\0';
	free(s1);
	return (s1_s2);
}
