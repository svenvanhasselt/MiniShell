/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_items.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 13:07:12 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/12 13:10:49 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_items(char const *s)
{
	int	switch_num;
	int	w_count;
	int	i;

	switch_num = 0;
	w_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			switch_num = 0;
		if (s[i] != ' ' && s[i] != '\n' && switch_num == 0)
		{
			switch_num = 1;
			w_count++;
		}
		i++;
	}
	return (w_count);
}
