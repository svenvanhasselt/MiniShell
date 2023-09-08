/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 16:10:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/07 16:19:02 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	free(lst);
	return (word_split);
}

void	add_node_env(char *string, int i, int *start, t_node **exp_lst)
{
	t_node	*node;
	char	*split_str;

	if (string[*start] == '?' && *start - 1 >= 0 && string[*start - 1] == '$')
	{
		node = make_node(ft_strdup("?"), 1, WORD, IN_DOUBLEQ);
		if (*start - 1 >= 0 && string[*start - 1] == '$')
			node->type = ENV;
		ft_add_back_list(exp_lst, node);
		*start = *start + 1;
	}
	if (*start < i)
	{
		split_str = null_check(ft_substr(string, *start, i - *start));
		node = make_node(split_str, ft_strlen(split_str), WORD, IN_DOUBLEQ);
		if (*start - 1 >= 0 && string[*start - 1] == '$')
			node->type = ENV;
		ft_add_back_list(exp_lst, node);
		*start = -1;
	}
}

void	split_string(char *string_node, t_node **exp_lst)
{
	int		i;
	int		start;
	int		len;
	char	*string;

	string = null_check(ft_strdup((string_node)));
	len = (int)ft_strlen(string);
	start = -1;
	i = 0;
	while (i <= len)
	{
		if ((string[i] != '$' && string[i] != ' ') && (start < 0))
			start = i;
		else if (((string[i] == '$' || string[i] == ' ' \
		|| i == (int)len) && start >= 0))
			add_node_env(string, i, &start, exp_lst);
		if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(exp_lst, make_node(null_check(ft_strdup("$")), \
			1, ENV, IN_DOUBLEQ));
		if (string[i] == ' ')
			ft_add_back_list(exp_lst, make_node(null_check(ft_strdup(" ")), \
			1, SPC, NORMAL));
		i++;
	}
	free(string);
}

t_node	*expand_split(t_node **head, char ***env, int exit_status)
{
	t_node	*exp_lst;
	t_node	*last;

	exp_lst = NULL;
	split_string((*head)->str, &exp_lst);
	expand_variable(&exp_lst, env, exit_status);
	last = ft_lastlist(exp_lst);
	last->next = (*head)->next;
	return (exp_lst);
}
