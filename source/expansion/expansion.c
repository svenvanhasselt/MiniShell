/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/15 17:48:00 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_nodes(char **split_variable, t_node *head)
{
	int	i;
	t_node *split_token;

	i = 1;
	while (split_variable[i])
	{
		split_token = make_node(split_variable[i], ft_strlen(split_variable[i]), WORD, NORMAL);
		split_token->next = head->next;
		head->next = split_token;
		head = head->next;
		i++;
	}
}

void	expand(t_node *head, char ***env, int exit_status)
{
	int		i;
	char	*input_str;
	char	**split_str;

	input_str = ft_strdup(head->str);
	free (head->str);
	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '$')
		{
			if (i != 0)
			{
				head->str = ft_substr(input_str, 0, i);
				input_str = ft_substr_free(input_str, i, ft_strlen(input_str), 1);
				split_str = ft_split(input_str, '$');
				add_nodes(split_str, head);
				break ;
			}
			else
			{
				split_str = split_variable(input_str, env, exit_status);
				head->str = split_str[0];
				add_nodes(split_str, head);
				break ;
			}
		}
		i++;
	}
}

void	expand_variable(t_node *lst, t_node *head, char ***env, int exit_status)
{
	while (lst)
	{
		if (lst->type == ENV)
		{
			if (!ft_strncmp(lst->str, "?", ft_strlen(lst->str)))
				lst->str = null_check(ft_strdup(null_check(ft_itoa(exit_status)))); //LEAK?
			else
				lst->str = find_variable(lst->str, env);
		}
		lst = lst->next;
	}
}

t_node	*expand_split(t_node *head, char ***env, int exit_status)
{
	int		i;
	int		start;
	char	*string;
	char	*split_str;
	t_node	*exp_lst;
	t_node	*node;

	exp_lst = NULL;
	string = ft_strdup(head->str);
	start = -1;
	i = 0;
	while (i <= ft_strlen(string))
	{
		if ((string[i] != '$' && string[i] != ' ') && (start < 0))
			start = i;
		else if (((string[i] == '$' || string[i] == ' ' || i == ft_strlen(string)) && start >= 0))
		{
			split_str = null_check(ft_substr(string, start, i - start));
			node = make_node(split_str, ft_strlen(split_str), WORD, NORMAL);
			if (string[start - 1] == '$')
				node->type = ENV;
			ft_add_back_list(&exp_lst, node);			
			start = -1;
		}
		else if (string[i] == '$' && string[i + 1] == '?')
		{
			ft_add_back_list(&exp_lst, make_node("?", 1, ENV, NORMAL));
		}
		if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(&exp_lst, make_node("$", 1, WORD, NORMAL));
		if (string[i] == ' ' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(&exp_lst, make_node(" ", 1, SPACE, NORMAL));
		i++;
	}
	expand_variable(exp_lst, head, env, exit_status);
	t_node *lst;
	t_node *last_node;
	
	last_node = ft_lastlist(exp_lst);
	last_node->next = head->next;
	head = exp_lst;
	
	while (exp_lst)
	{
		printf("e-l: %s\n", exp_lst->str);
		exp_lst = exp_lst->next;
	}
	return (last_node);
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;
	t_node	*temp;

	head = *lst;
	while (head)
	{
		if (head->type == ENV || (head->state == IN_DOUBLEQ && ft_strnstr(head->str, "$", head->len)))
		{
			temp = head;
			if (head->state == IN_DOUBLEQ)
				head->str = ft_strtrim_free(head->str, "\"");
			head = expand_split(head, env, exit_status);
			free(temp);
		}
		// else if ()
		// 	expand_split(&head, env, exit_status);
		head = head->next;
	}
}
