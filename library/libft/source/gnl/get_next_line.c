/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 11:20:14 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/09 11:40:39 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	size_t		i;
	static char	*store;
	char		*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_process_text(fd, store);
	if (!store)
		return (NULL);
	i = 0;
	while (store[i] != '\n' && store[i])
			i++;
	ret_str = ft_substr_free(store, 0, i + 1, 0);
	if (!ret_str)
		return (free(store), NULL);
	store = ft_substr_free(store, i + 1, ft_strlen(store) - i, 1);
	if (!store)
		return (free(ret_str), NULL);
	return (ret_str);
}
