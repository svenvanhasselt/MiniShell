/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:51:49 by psadeghi          #+#    #+#             */
/*   Updated: 2023/08/07 17:44:49 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	dq_tokens(t_node **lst, char *line, int i)
{
	// dq_start = i;
	// i++;
	// while (line[i] != '\0' && line[i] != '\"')
	// 	i++;
	// size = i - dq_start + 1;
	// // if (line[i] == '\0')
	// // {
	// // 	printf("this is the size in if in double qoute %d\n", size);
	// // 	new = ft_substr(line, dq_start, (size_t)(size));
	// // 	printf("this is new string in if in dq = \"%s\" and the char '%d'\n", new, line[i]);
	// // 	ft_add_back_list(lst, make_node(new, size, WORD, IN_DOUBLEQ));
	// // 	break;
	// // }
	// // else
	// // {
	// printf("this is the size in else in double qoute %d\n", size);
	// new = ft_substr(line, dq_start, (size_t)(size));
	// printf("this is new string in else in double qoute = \"%s\" and the char '%c'\n", new, line[i]);
	// ft_add_back_list(lst, make_node(new, size, WORD, IN_DOUBLEQ));
	// // }
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
	printf("this is the size in else in double qoute %d\n", size);
	new = ft_substr(line, dq_start, (size_t)(size));
	printf("this is new string in else in double qoute = \"%s\" and the char '%c'\n", new, line[i]);
	ft_add_back_list(lst, make_node(new, size, WORD, IN_DOUBLEQ));
	return (i);
}

int	sq_tokens(t_node **lst, char *line, int i)
{
	// sq_start = i;
	// i++;
	// while (line[i] != '\0' && line[i] != '\'')
	// 	i++;
	// size = i - sq_start + 1;
	// // if (line[i] == '\0')
	// // {
	// // 	printf("this is the size in if in double qoute %d\n", size);
	// // 	new = ft_substr(line, sq_start, (size_t)(size));
	// // 	printf("this is new string in if in dq = \"%s\" and the char '%c'\n", new, line[i]);
	// // 	ft_add_back_list(lst, make_node(new, size, WORD, IN_SINGLEQ));
	// // 	break;
	// // }
	// // else
	// // {
	// printf("this is the size in else in double qoute %d\n", size);
	// new = ft_substr(line, sq_start, (size_t)(size));
	// printf("this is new string in else in double qoute = \"%s\" and the char '%d'\n", new, line[i]);
	// ft_add_back_list(lst, make_node(new, size, WORD, IN_SINGLEQ));
	// // }
	int		sq_start;
	int		size;
	char	*new;

	sq_start = i;
	i++;
	while (line[i] != '\0' && line[i] != '\'')
		i++;
	size = i - sq_start + 1;
	printf("this is the size in else in double qoute %d\n", size);
	new = ft_substr(line, sq_start, (size_t)(size));
	printf("this is new string in else in double qoute = \"%s\" and the char '%d'\n", new, line[i]);
	ft_add_back_list(lst, make_node(new, size, WORD, IN_SINGLEQ));
	return (i);
}

void	make_tokens(char *line, t_node **lst)
{
	int		i;
	int		start;
	char	*new;
	int		size;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			new = ft_substr(line, i, (size_t)(1));
			printf("this is new string first if= \"%s\" and the char '%c'\n", new, line[i]);
			ft_add_back_list(lst, make_node(new, 1, line[i], NORMAL));
			i++;
		}
		start = i;
		printf("this is the start char = %c\n", line[start]);
		while (line[i] != '\0' && !(line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\"' || line[i] == '\''))
		{
			i++;
		}
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\"' || line[i] == '\'')
		{
			size = i - start;
			if (size != 0)
			{
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in if= \"%s\" and the char '%c'\n", new, line[i]);
				if (line[start] == '$')
					ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
				else
					ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
			}
			if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				printf("this is the size = %d\n", size);
				new = ft_substr(line, i, (size_t)(1));
				printf("this is new string in the same if= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, 1, line[i], NORMAL));
			}
			if (line[i] == '\"')
				i = dq_tokens(lst, line, i);
			else if (line[i] == '\'')
				i = sq_tokens(lst, line, i);
		}
		else
		{
			size = i - start;
			printf("second = this is the start char = %d\n", line[start]);
			if (line[start] == '\0' && line[i] == '\0')
			{
				printf("it was me! sorry :D \n");
				break;
			}
			else
			{
				if (line[i] == '\0')
				{
					printf("this is the size in if in else %d\n", size);
					new = ft_substr(line, start, (size_t)(size));
					printf("this is new string in else = \"%s\" and the char '%d'\n", new, line[i]);
					if (line[start] == '$')
						ft_add_back_list(lst, make_node(new, size, ENV, NORMAL));
					else
						ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
					break;
				}
				else
				{
					printf("this is the size in else %d\n", size);
					new = ft_substr(line, start, (size_t)(size));
					printf("this is new string in else in else = \"%s\" and the char '%d'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
				}
			}
		}
		if (line[i] != '\0')
			i++;
	}
	printf("this is the last result->");
	print_list(*lst);
	printf("we got out from here\n");
}

