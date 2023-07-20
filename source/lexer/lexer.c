/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/20 12:39:40 by svan-has      ########   odam.nl         */
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
	// int		env_start;
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
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
			}
			if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				size = 1;
				new = ft_substr(line, i, (size_t)(size));
				printf("this is new string in the same if= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
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
				ft_add_back_list(lst, make_node(new, size, line[dq_start], IN_DOUBLEQ));
				print_list(*lst);
				if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
				{
					size = 1;
					new = ft_substr(line, i, (size_t)(size));
					printf("this is new string after dq= \"%s\" and the char '%c'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
					// i++;
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
					// i++;
				}
			}
			//else if (line[i] != '\0')
			//for which case I have added the previous line?
			// it was for this "ls -l >"
			else
			{
				size = i - start;
				if (size == 0 && line[i] == '\0')
				{
					printf("I will get here for %d this\n", line[i]);
					// ft_add_back_list(lst, NULL);
					break;
				}
				else
				{
					printf("this is the size in else %d\n", size);
					new = ft_substr(line, start, (size_t)(size));
					printf("this is new string in else = \"%s\" and the char '%d'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
				}
			}
		}
		i++;
	}
	printf("this is the last result->");
	print_list(*lst);
	// make_node_parser(lst);
	//make_parser(lst);
	printf("we got out from here\n");
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
	t_parser_list *p_list;
	// t_parser_list *head;

	p_list = NULL;
	
	lst = NULL;
	while(1)
	{
		printf("each time\n");
		free_llist(&p_list);
		free_tokens(&lst);
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
			make_parser(&lst, &p_list);
			print_list_lparser(&p_list);
			add_history(line);
			execution(&p_list);
		}
	}
	return (line);
}

void	free_tokens(t_node **lst)
{
	t_node *temp;

	while (*lst)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}
