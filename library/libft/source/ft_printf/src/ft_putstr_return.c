/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 18:32:09 by svan-has      #+#    #+#                 */
/*   Updated: 2022/11/01 14:22:32 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_return(char *s, int fd)
{
	int	count;

	count = 0;
	if (s == NULL)
	{
		ft_putstr_return("(null)", 1);
		return (6);
	}
	while (*s)
	{
		write(fd, &(*s++), 1);
		count++;
	}
	return (count);
}
