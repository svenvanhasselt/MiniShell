/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 14:45:25 by svan-has      #+#    #+#                 */
/*   Updated: 2022/11/01 15:55:27 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	error_check(const char *s)
{
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s != 'x' && *s != 'X' && *s != 'c' && *s != 's' && *s != 's'
				&& *s != 'd' && *s != 'i' && *s != 'u' && *s != '%'
				&& *s != 'p')
				return (0);
		}
		s++;
	}
	return (1);
}

int	convert_base(unsigned long int arg, int base, char c)
{
	int				count;
	unsigned int	arg_x;
	char			*rep;

	rep = "0123456789abcdef";
	arg_x = (unsigned int)arg;
	count = 0;
	if (arg / base > 0 && c == 'p')
		count += convert_base((arg / base), base, c);
	else if (arg_x / base > 0)
		count += convert_base((arg_x / base), base, c);
	if (c == 'X' && ft_isalpha(rep[arg_x % base]))
		count += ft_putchar_return(rep[arg_x % base] - 32, 1);
	else if (c == 'x')
		count += ft_putchar_return(rep[arg_x % base], 1);
	else
		count += ft_putchar_return(rep[arg % base], 1);
	return (count);
}

int	check_format_arg(const char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == '%')
		count += ft_putchar_return('%', 1);
	else if (c == 's')
		count += ft_putstr_return(va_arg(arg, char *), 1);
	else if (c == 'c')
		count += ft_putchar_return(va_arg(arg, int), 1);
	else if (c == 'x' || c == 'X')
		count += convert_base(va_arg(arg, unsigned int), 16, c);
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_return(va_arg(arg, int), 1);
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(arg, unsigned int), 1);
	else if (c == 'p')
	{
		count += ft_putstr_return("0x", 1);
		count += convert_base(va_arg(arg, unsigned long int), 16, c);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		returnval;
	va_list	arg;

	returnval = 0;
	if (!error_check(format))
		return (-1);
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
			returnval += check_format_arg(*++format, arg);
		else if (*format != '%')
			returnval += ft_putchar_return(*format, 1);
		format++;
	}
	va_end(arg);
	return (returnval);
}
