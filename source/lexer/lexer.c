/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/21 13:47:06 by psadeghi      ########   odam.nl         */
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
	new = null_check(ft_substr(line, dq_start, (size_t)(size)));
	ft_add_back_list(lst, make_node(new, size, WORD, IN_DOUBLEQ));
	free(new);
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
	free(new);
	return (i);
}

int	env_check(char *line, int i, int start)
{
	while(line[start] != '\0' && start < i)
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
		printf("in the while\n");
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
	printf("after the while\n");
	printf("this is the lexer list:\n");
	print_list(*lst);
	printf("thats it\n");
}
