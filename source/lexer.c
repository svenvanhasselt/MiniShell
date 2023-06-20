/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/20 16:31:22 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_checkline(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while(s[i])
// 	{
// 		if (s[i] == '|' || s[i] == '<' || s[i] == '>'
// 		|| s[i] == '$' || s[i] == '\'' || s[i] == '\"')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	check_line(char *line)
{
	int	i;
	int	start;
	char	*new;
	int		size;
	int		dq_start;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		start = i;
		while (line[i] != '\0' && !(line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\"'))
		{
			i++;
		}
		// if (line[i] == '\"')
		// {
		// 	dq_start = i;
		// 	i++;
		// 	while(line[i] != '\0' && line[i] != '\"')
		// 		i++;
		// 	if (line[i] == '\"')
		// 		i++;
		// 	size = i - dq_start;
		// 	new = ft_substr(line, start, (size_t)(size));
		// 	printf("this is string in double qoute= \"%s\" and the char '%c'\n", new, line[i]);
		// }
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			size = i - start;
			printf("this is the size in if %d\n", size);
			if (size != 0)
			{
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in if= \"%s\" and the char '%c'\n", new, line[i]);
			}
			if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				size = 1;
				new = ft_substr(line, i, (size_t)(size));
				printf("this is new string in the same if= \"%s\" and the char '%c'\n", new, line[i]);
			}
		}
		else
		{
			if (line[i] == '\"')
			{
				dq_start = i;
				i++;
				while(line[i] != '\0' && line[i] != '\"')
					i++;
				if (line[i] == '\"')
					i++;
				size = i - dq_start;
				new = ft_substr(line, start, (size_t)(size));
				printf("this is string in double qoute= \"%s\" and the char '%c'\n", new, line[i]);
			}
			else
			{
				size = i - start;
				printf("this is the size in else %d\n", size);
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in else = \"%s\" and the char '%c'\n", new, line[i]);
			}
		}
		i++;
	}
}
// t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state)
// {
// 	t_node	*node;

// 	node = (t_node *)malloc(sizeof(t_node));
// }
char	*ft_readline(char *prompt)
{
	char	*line;
	// int		res;
	// int		words;
	// int		prev_words;
	// char	**new;
	
	while(1)
	{
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		else
		{
			printf("line = %s\n", line);
			check_line(line);
			// res = ft_checkline(line);
			// printf("this is the res =%d\n", res);
			// words = count_words_msh(line);
			// printf("this is new word count = %d\n", words);
			// prev_words = count_words(line, ' ');
			// printf("this is prev word count = %d\n", prev_words);
			// new = (char **)malloc(sizeof(char *) * (count_words_msh(line) + 1));
			// if (!new)
			// 	return(NULL);
			// count_arrays_msh(line, new);
			add_history(line);
		}
	}
	return (line);
}

// t_node	*make_node(char *line)
// {
// 	i
// }

// t_lst	make_list(char *line)
// {
// 	t_lst *list;
// 	int	start;
// 	int	i;

// 	i = 0;
// 	start = 0;
// 	list = (t_lst *)malloc(sizeof(t_lst));
// 	while(line)
// 	{
		
// 	}
// }

// t_test {
// 	e_token	type;
// }

// t_test test;

// test->type = WORD;