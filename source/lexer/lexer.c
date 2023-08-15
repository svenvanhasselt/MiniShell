/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/15 12:20:31 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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
	new = ft_substr(line, dq_start, (size_t)(size));
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
	new = ft_substr(line, sq_start, (size_t)(size));
	ft_add_back_list(lst, make_node(new, size, WORD, IN_SINGLEQ));
	return (i);
}

int	make_new_token(t_node **lst, char *line, int i, int start)
{
	int		size;
	char	*new;

	size = i - start;
	if (size != 0)
	{
		new = ft_substr(line, start, (size_t)(size));
		if (line[start] == '$')
			ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
		else
			ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
	}
	if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
	{
		new = ft_substr(line, i, (size_t)(1));
		ft_add_back_list(lst, make_node(new, 1, line[i], NORMAL));
	}
	if (line[i] == '\"')
		i = dq_tokens(lst, line, i);
	else if (line[i] == '\'')
		i = sq_tokens(lst, line, i);
	return (i);
}

int	make_new_token2(t_node **lst, char *line, int i, int start)
{
	int		size;
	char	*new;

	size = i - start;
	if (!(line[start] == '\0' && line[i] == '\0'))
	{
		if (line[i] == '\0')
		{
			new = ft_substr(line, start, (size_t)(size));
			if (line[start] == '$')
				ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
			else
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
		}
		else
		{
			new = ft_substr(line, start, (size_t)(size));
			ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
		}
	}
	return (i);
}

void	make_tokens(char *l, t_node **lst)
{
	int		i;
	int		start;
	char	*new;

	i = 0;
	while (l[i] != '\0')
	{
		if (l[i] == ' ' || l[i] == '>' || l[i] == '<' || l[i] == '|')
		{
			new = ft_substr(l, i, (size_t)(1));
			ft_add_back_list(lst, make_node(new, 1, l[i], NORMAL));
			i++;
		}
		start = i;
		while (l[i] != '\0' && !(l[i] == ' ' || l[i] == '>' || \
		l[i] == '<' || l[i] == '|' || l[i] == '\"' || l[i] == '\''))
			i++;
		if (l[i] == ' ' || l[i] == '>' || l[i] == '<' || \
		l[i] == '|' || l[i] == '\"' || l[i] == '\'')
			i = make_new_token(lst, l, i, start);
		else
			i = make_new_token2(lst, l, i, start);
		if (l[i] != '\0')
			i++;
	}
}
