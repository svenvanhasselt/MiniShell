/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_num.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:40:25 by svan-has      #+#    #+#                 */
/*   Updated: 2023/04/18 15:54:45 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char	**copy_string(char **split_string, const char *s, int numbers)
{
	int		i;
	int		j;
	int		row;

	i = 0;
	row = 0;
	split_string = (char **) malloc ((numbers + 1) * sizeof(char *));
	if (split_string == NULL)
		return (NULL);
	while (s[i])
	{
		j = 0;
		while (ft_isdigit(s[i++]))
			j++;
		if (j > 0)
		{
			split_string[row++] = ft_substr(s, i - j - 1, j);
			if (!split_string[row - 1])
				return (del_split(split_string, row - 1));
		}
	}
	split_string[row] = 0;
	return (split_string);
}

static int	*copy_numbers(char **split_string, int numbers)
{
	int		i;
	int		*split_num;

	split_num = malloc (numbers * sizeof(int));
	if (!split_num)
		return (NULL);
	i = 0;
	while (i < numbers)
	{
		split_num[i] = ft_atoi(split_string[i]);
		i++;
	}
	del_split(split_string, numbers - 1);
	return (split_num);
}

int	*ft_split_num(char const *s)
{
	char	**split_string;
	int		numbers;

	if (!s)
		return (NULL);
	split_string = NULL;
	numbers = ft_count_items(s);
	split_string = copy_string(split_string, s, numbers);
	if (!split_string)
		return (NULL);
	return (copy_numbers(split_string, numbers));
}
