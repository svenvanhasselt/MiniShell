/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 09:31:57 by svan-has      #+#    #+#                 */
/*   Updated: 2023/05/07 11:34:19 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_nline(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_process_text(int fd, char *store)
{
	int			rd;
	char		*buffer;

	buffer = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd != 0 && find_nline(store) == 0)
	{
		rd = read (fd, buffer, BUFFER_SIZE);
		if (rd == -1 || (!rd && ft_strlen(store) == 0))
			return (free(buffer), free(store), NULL);
		buffer[rd] = '\0';
		store = ft_strjoin_free(store, buffer);
		if (!store)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (store);
}
