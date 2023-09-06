/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/06 16:14:24 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	env_check(char *line, int i, int start)
{
	while (line[start] != '\0' && start < i)
	{
		if (line[start] == '$')
			return (1);
		start++;
	}
	return (0);
}

int	make_new_token(t_node **lst, char *line, int i, int start)
{
	int		size;
	char	*new;

	size = i - start;
	if (size != 0)
	{
		new = null_check(ft_substr(line, start, (size_t)(size)));
		if (env_check(line, i, start) == 1)
			ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
		else
			ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
	}
	if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
	{
		new = null_check(ft_substr(line, i, (size_t)(1)));
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
			new = null_check(ft_substr(line, start, (size_t)(size)));
			if (env_check(line, i, start) == 1)
				ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
			else
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
		}
		else
		{
			new = null_check(ft_substr(line, start, (size_t)(size)));
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
			new = null_check(ft_substr(l, i, (size_t)(1)));
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
	// print_list(*lst);
}
