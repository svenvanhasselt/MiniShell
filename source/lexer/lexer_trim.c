/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_trim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 14:56:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/11 12:55:36 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"

char	*lexer_trim(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = NULL;
	j = ft_strlen(str) - 1;
	if (str != NULL)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' \
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f'))
			i++;
		while (j > i && (str[j] && (str[j] == ' ' || \
		str[j] == '\t' || str[j] == '\r' \
		|| str[j] == '\n' || str[j] == '\v' || str[j] == '\f')))
			j--;
		if (j > i)
			new = ft_substr(str, i, (j - i) + 1);
		else
			new = ft_strdup("");
	}
	return (new);
}
