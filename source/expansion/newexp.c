/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newexp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 14:43:49 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_variable(char *variable, enum e_token type, char ***env)
{
	int		var_set;
	char	*value;

	var_set = find_env_var(variable, (*env));
	if (var_set >= 0)
	{
		value = null_check(ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
		free(variable);
		return (value);
	}
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (variable);
	else if (type == EXP)
		return (NULL);
	return (NULL);
}

t_node	*split_variable(t_node *lst)
{
	int		i;
	char	**split_str;
	t_node	*word_split;
	t_node	*node;


	word_split = NULL;
	split_str = null_check(ft_split(lst->str, ' '));
	free(lst->str);
	i = 0;
	while (split_str[i])
	{
		node = make_node(split_str[i], ft_strlen(split_str[i]), lst->type, EXP);
		ft_add_back_list(&word_split, node);
		i++;
	}
	node = ft_lastlist(word_split);
	node->next = lst->next;
	// free(lst);
	return (word_split);
}
void	expand_variable(t_node **lst, char ***env, int exit_status, bool split)
{	
	t_node	*head;
	t_node	*prev;
	t_node	*node;

	head = *lst;
	prev = head;
	while (head)
	{
		if (head->type == ENV)
		{
			if (!ft_strncmp(head->str, "?", ft_strlen(head->str)))
				head->str = null_check(ft_strdup(null_check(ft_itoa(exit_status)))); //LEAK?
			else
			{
				head->str = find_variable(head->str, head->type, env);
				if (ft_strnstr(head->str, " ", ft_strlen(head->str)) && split == true)
					node = split_variable(head);
				if (*lst == head)
					*lst = node;
				else
					prev = node;
			}
		}
		prev = head;
		head = head->next;
	}
}

t_node	*expand_split(t_node **head, char ***env, int exit_status, bool split)
{
	int		i;
	int		start;
	int		len;
	char	*string;
	char	*split_str;
	t_node	*exp_lst;
	t_node	*node;
	t_node	*last_node;

	exp_lst = NULL;
	string = ft_strdup((*head)->str);
	len = (int)ft_strlen(string);
	start = -1;
	i = 0;
	while (i <= len)
	{
		if ((string[i] != '$' && string[i] != ' ') && (start < 0))
			start = i;
		else if (((string[i] == '$' || string[i] == ' ' || i == (int)len) && start >= 0))
		{
			split_str = null_check(ft_substr(string, start, i - start));
			node = make_node(split_str, ft_strlen(split_str), WORD, IN_DOUBLEQ);
			if (string[start - 1] == '$')
				node->type = ENV;
			ft_add_back_list(&exp_lst, node);			
			start = -1;
		}
		if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(&exp_lst, make_node("$", 1, ENV, IN_DOUBLEQ));
		if (string[i] == ' ')
			ft_add_back_list(&exp_lst, make_node(" ", 1, SPACE, NORMAL));
		i++;
	}
	expand_variable(&exp_lst, env, exit_status, split);
	last_node = ft_lastlist(exp_lst);
	last_node->next = (*head)->next;	
	return (exp_lst);
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;
	t_node  *prev;
	t_node	*node;
	bool	split;

	head = *lst;
	prev = *lst;
	while (head)
	{
		split = true;
		if (head->state == IN_DOUBLEQ)
			split = false;
		if (head->type == ENV || (head->state == IN_DOUBLEQ && ft_strnstr(head->str, "$", head->len)))
		{
			if (head->state == IN_DOUBLEQ)
				head->str = ft_strtrim_free(head->str, "\"");
			node = expand_split(&head, env, exit_status, split);
			if (*lst == head)
				*lst = node;
			else
				prev->next = node;
		}
		prev = head;
		head = head->next;
	}
}
