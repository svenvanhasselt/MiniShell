/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 11:23:59 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/07 11:38:55 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h> 
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*read_process_text(int fd, char *store);
size_t	find_nline(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
