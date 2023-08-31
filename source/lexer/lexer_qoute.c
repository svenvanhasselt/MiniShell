/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_qoute.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:29:36 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/30 15:30:02 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dq_tokens(t_node **lst, char *line, int i)
{
	int		dq_start;
	int		size;
	char	*new;

	dq_start = i;
	i++;
	while (line[i] != '\0' && line[i] != '\"')
		i++;
	if (line[i] == '\0')
		size = i - dq_start;
	else
		size = i - dq_start + 1;
	new = null_check(ft_substr(line, dq_start, (size_t)(size)));
	ft_add_back_list(lst, make_node(new, size, WORD, IN_DOUBLEQ));
	return (i);
}

int	sq_tokens(t_node **lst, char *line, int i)
{
	int		sq_start;
	int		size;
	char	*new;

	sq_start = i;
	i++;
	while (line[i] != '\0' && line[i] != '\'')
		i++;
	size = i - sq_start + 1;
	new = null_check(ft_substr(line, sq_start, (size_t)(size)));
	ft_add_back_list(lst, make_node(new, size, WORD, IN_SINGLEQ));
	return (i);
}
