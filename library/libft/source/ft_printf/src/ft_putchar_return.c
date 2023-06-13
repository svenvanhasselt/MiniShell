/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ret_putchar_fd.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 18:23:02 by svan-has      #+#    #+#                 */
/*   Updated: 2022/11/01 14:16:32 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_return(char c, int fd)
{
	return (write(fd, &c, 1));
}
