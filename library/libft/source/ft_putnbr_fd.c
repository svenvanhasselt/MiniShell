/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:47:52 by svan-has          #+#    #+#             */
/*   Updated: 2022/10/21 17:15:04 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	numb;

	numb = 0;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 10)
	{
		numb = (n % 10) + 48;
		ft_putnbr_fd(n /= 10, fd);
		ft_putchar_fd(numb, fd);
	}
	else
	{
		ft_putchar_fd((n % 10) + 48, fd);
	}
}
