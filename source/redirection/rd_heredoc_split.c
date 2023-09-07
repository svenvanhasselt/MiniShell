/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 15:32:53 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/07 15:34:14 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_split_string_utils(t_node **exp_lst, char *string, int i)
{
	if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
		ft_add_back_list(exp_lst, make_node(null_check(ft_strdup("$")), \
		1, ENV, IN_DOUBLEQ));
	if (string[i] == ' ')
		ft_add_back_list(exp_lst, make_node(null_check(ft_strdup(" ")), \
		1, SPC, NORMAL));
	if (string[i] == '\'')
		ft_add_back_list(exp_lst, make_node(null_check(ft_strdup("\'")), \
		1, SINGLE_QOUTE, NORMAL));
	if (string[i] == '\"')
		ft_add_back_list(exp_lst, make_node(null_check(ft_strdup("\"")), \
		1, DOUBLE_QOUTE, NORMAL));
}

void	heredoc_split_string(char *string_node, t_node **exp_lst)
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
		if ((string[i] != '$' && string[i] != ' ' && string[i] != '\'' \
		&& string[i] != '\"') && (start < 0))
			start = i;
		else if (((string[i] == '$' || string[i] == ' ' || \
		string[i] == '\'' || string[i] == '\"'\
		|| i == (int)len) && start >= 0))
			add_node_env(string, i, &start, exp_lst);
		if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(exp_lst, make_node(null_check(ft_strdup("$")), \
			1, ENV, IN_DOUBLEQ));
		heredoc_split_string_utils(exp_lst, string, i);
		i++;
	}
	free(string);
}

t_node	*heredoc_expand_split(t_node **head, char ***env)
{
	t_node	*exp_lst;
	t_node	*last;

	exp_lst = NULL;
	heredoc_split_string((*head)->str, &exp_lst);
	heredoc_expand_variable(&exp_lst, env, 0);
	last = ft_lastlist(exp_lst);
	last->next = (*head)->next;
	return (exp_lst);
}
