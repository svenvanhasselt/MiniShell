/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/16 14:20:49 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *prompt)
{
	char	*line;
	int		res;
	int		words;
	int		prev_words;
	
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
			res = ft_checkline(line);
			printf("this is the res =%d\n", res);
			words = count_words_msh(line);
			printf("this is new word count = %d\n", words);
			prev_words = count_words(line, ' ');
			printf("this is prev word count = %d\n", prev_words);
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