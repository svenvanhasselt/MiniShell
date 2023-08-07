/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 10:03:47 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/21 14:15:26 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(set))
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	trimleft(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (ft_isset(set, s1[i]))
		i++;
	return (i);
}

static int	trimright(char const *s1, char const *set)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while ((ft_isset(set, s1[i])))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trimmed;
	int		start_pos;
	int		len;

	if (s1 == 0 || set == 0)
		return (NULL);
	start_pos = trimleft(s1, set);
	len = trimright(s1, set) - start_pos;
	s1_trimmed = ft_substr(s1, start_pos, len);
	return (s1_trimmed);
}
