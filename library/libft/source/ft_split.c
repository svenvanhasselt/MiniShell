/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:40:25 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/21 12:45:28 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	switch_num;
	int	w_count;

	switch_num = 0;
	w_count = 0;
	while (*s)
	{
		if (*s != c && switch_num == 0)
		{
			switch_num = 1;
			w_count++;
		}
		if (*s == c)
			switch_num = 0;
		s++;
	}
	return (w_count);
}

static char	**del_split(char **split_string, int row)
{
	while (row >= 0)
	{
		free(split_string[row]);
		row--;
	}
	free(split_string);
	return (NULL);
}

static char	**copy_string(char **split_string, const char *s, char c)
{
	int		i;
	int		start;
	int		row;

	i = 0;
	start = -1;
	row = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && start >= 0)
		{
			split_string[row++] = ft_substr(s, start, i - start);
			if (!split_string[row - 1])
				return (del_split(split_string, row - 1));
			start = -1;
		}
		i++;
	}
	split_string[row] = 0;
	return (split_string);
}

char	**ft_split(char const *s, char c)
{
	char	**split_string;

	if (!s)
		return (NULL);
	split_string = (char **) malloc ((count_word(s, c) + 1) * sizeof(char *));
	if (split_string == NULL)
		return (NULL);
	split_string = copy_string(split_string, s, c);
	return (split_string);
}
