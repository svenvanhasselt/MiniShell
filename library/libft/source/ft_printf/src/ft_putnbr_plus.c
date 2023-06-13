/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_plus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 18:47:52 by svan-has      #+#    #+#                 */
/*   Updated: 2022/11/01 14:23:09 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_return(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		count += ft_putstr_return("-2147483648", fd);
	else if (n < 0)
	{
		count += ft_putchar_return('-', fd);
		count += ft_putnbr_return((n *= -1), fd);
	}
	else if (n >= 10)
	{
		count += ft_putnbr_return(n / 10, fd);
		count += ft_putchar_return((n % 10) + 48, fd);
	}
	else
		count += ft_putchar_return((n % 10) + 48, fd);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10, fd);
	count += ft_putchar_return((n % 10) + 48, fd);
	return (count);
}
