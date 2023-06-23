/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/23 14:41:19 by psadeghi      ########   odam.nl         */
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

void	check_line(char *line, t_node **lst)
{
	int	i;
	int	start;
	char	*new;
	int		size;
	int		dq_start;
	int		sq_start;
	int		env_start;
	// t_node	*lst;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			size = 1;
			new = ft_substr(line, i, (size_t)(size));
			// ft_add_back_list(&lst, make_node(new, size, line[i], NORMAL));
			// print_list(lst);
			printf("this is new string first if= \"%s\" and the char '%c'\n", new, line[i]);
			ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
			// print_list(*lst);
			i++;
		}
		start = i;
		while (line[i] != '\0' && !(line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\"' || line[i] == '\''))
		{
			i++;
		}
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			size = i - start;
			printf("this is the size in if %d\n", size);
			if (size != 0)
			{
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in if= \"%s\" and the char '%c'\n", new, line[i]);
				// if (!(*lst))
				// {
				// 	*lst = make_node(new, size, line[i], NORMAL);
				// 	(*lst)->next = NULL;
				// ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
				// print_list(*lst);
				// 	print_list(*lst);
				// }
			}
			if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				size = 1;
				new = ft_substr(line, i, (size_t)(size));
				printf("this is new string in the same if= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
				// print_list(*lst);
			}
		}
		else
		{
			if (line[i] == '\"')
			{
				dq_start = i;
				i++;
				while(line[i] != '\0' && line[i] != '\"')
				{
					// if(line[i] == '$')
					// {
					// 	printf("hi this is %c and the index= %d\n", line[i], i);
					// 	env_start = i;
					// 	while(line[i] != ' ' && line[i] != '\0' && line[i] != '\"')
					// 		i++;
					// 	printf("and this the end with char = %c and index = %d\n", line[i], i);
					// 	size = i - env_start;
					// 	new = ft_substr(line, env_start, (size_t)(size));
					// 	printf("this is ENV string in the Double qoute= \"%s\" and the char '%c'\n", new, line[i]);
					// 	ft_add_back_list(lst, make_node(new, size, ENV, IN_DOUBLEQ));
					// }
					i++;
				}
				if (line[i] == '\"')
					i++;
				size = i - dq_start;
				new = ft_substr(line, start, (size_t)(size));
				printf("this is string in double qoute= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[dq_start], IN_DOUBLEQ));
				print_list(*lst);
				if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
				{
					size = 1;
					new = ft_substr(line, i, (size_t)(size));
					printf("this is new string after dq= \"%s\" and the char '%c'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
					// print_list(*lst);
				}
			}
			else if (line[i] == '\'')
			{
				sq_start = i;
				i++;
				while(line[i] != '\0' && line[i] != '\'')
					i++;
				if (line[i] == '\'')
					i++;
				size = i - sq_start;
				new = ft_substr(line, start, (size_t)(size));
				printf("this is string in single qoute= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[sq_start], IN_SINGLEQ));
				print_list(*lst);
				if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
				{
					size = 1;
					new = ft_substr(line, i, (size_t)(size));
					printf("this is new string after sq= \"%s\" and the char '%c'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
					// print_list(*lst);
				}
			}
			else
			{
				size = i - start;
				printf("this is the size in else %d\n", size);
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in else = \"%s\" and the char '%c'\n", new, line[i]);
				// ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
				// print_list(*lst);
			}
		}
		i++;
	}
	printf("this is the last result->");
	print_list(*lst);
}

t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(1);
	// printf("hi hi\n");
	node->str = str;
	node->len = len;
	// printf("hi hi1\n");
	node->type = type;
	// printf("hi hi2\n");
	node->state = state;
	// printf("hi hi3\n");
	node->next = NULL;
	node->prev = NULL;
	// printf("hi hi4\n");
	return (node);
}

t_node	*ft_lastlist(t_node *lst)
{
	if (!lst)
		return (0);
	// printf("hi hi9\n");
	while (lst->next)
		lst = lst->next;
	// printf("hi hi10\n");
	return (lst);
}

void	ft_add_back_list(t_node **lst, t_node *new)
{
	t_node	*current;

	if (!new || !lst)
		return ;
	// printf("hi hi5\n");
	if (!*lst)
	{
		// printf("hi hi6\n");
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	// printf("hi hi7\n");
	current = ft_lastlist(*lst);
	// printf("hi hi8\n");
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist(t_node *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	print_list(t_node *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= %s, state= %u, ", lst->str, lst->state);
		printf("type= %d ,", lst->type);
		lst = lst->next;
	}
	printf("str= %s, state= %u ", lst->str, lst->state);
	printf("type= %d\n", lst->type);
}

char	*ft_readline(char *prompt)
{
	char	*line;
	t_node	*lst;
	// int		res;
	// int		words;
	// int		prev_words;
	// char	**new;
	
	lst = NULL;
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
			check_line(line, &lst);
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