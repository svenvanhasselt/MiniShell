/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:23:12 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/09 11:40:00 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}
