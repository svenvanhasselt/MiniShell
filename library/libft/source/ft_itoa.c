/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-has <svan-has@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:47:24 by sven              #+#    #+#             */
/*   Updated: 2022/10/26 17:19:45 by svan-has         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numb(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*copy_number(char *number, long int n, long int i)
{
	if (n == 0)
		number[0] = '0';
	while (n > 0)
	{
		number[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (number);
}

char	*ft_itoa(int n)
{
	char		*number;
	long int	end;
	long int	n_new;

	n_new = (long int)n;
	end = count_numb(n_new);
	if (n_new < 0)
	{
		number = (char *) malloc (end + 2 * sizeof(char));
		if (number == NULL)
			return (NULL);
		number[0] = '-';
		end++;
		n_new *= -1;
	}
	else
	{
		number = (char *) malloc (end + 1 * sizeof(char));
		if (number == NULL)
			return (NULL);
	}
	number = copy_number(number, n_new, end - 1);
	number[end] = '\0';
	return (number);
}
