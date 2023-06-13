/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:06:03 by svan-has      #+#    #+#                 */
/*   Updated: 2022/11/01 16:18:45 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_printf(const char *format, ...);
int		ft_putchar_return(char c, int fd);
int		ft_putstr_return(char *s, int fd);
int		ft_putnbr_return(int n, int fd);
int		ft_putnbr_unsigned(unsigned int n, int fd);
int		ft_isalpha(int x);
#endif