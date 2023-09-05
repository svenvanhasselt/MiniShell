/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc_exp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 13:16:27 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/05 10:37:25 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*heredoc_expand(t_node *head, t_node *node)
{
	if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
		node = split_variable(head);
	return (node);
}

void	heredoc_expand_variable(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;
	t_node	*prev;

	head = *lst;
	prev = head;
	while (head)
	{
		if (head->type == ENV)
		{
			if (!ft_strncmp(head->str, "?", ft_strlen(head->str)))
				expand_exit_code(head, exit_status);
			else
			{
				head->str = heredoc_find_variable(head->str, head->type, env);
				if (*lst == head)
					*lst = heredoc_expand(head, *lst);
				else
					prev = heredoc_expand(head, prev);
			}
		}
		prev = head;
		head = head->next;
	}
}

void	hd_make_node(char *str, t_node **l, t_node *node, char *split_str)
{
	int	i;
	int	start;
	int	len;

	i = -1;
	start = -1;
	len = (int)ft_strlen(str);
	while (++i <= len)
	{
		if ((str[i] != '$' && str[i] != ' ') && (start < 0))
			start = i;
		else if (((str[i] == '$' || str[i] == ' ' || i == len) && start >= 0))
		{
			split_str = null_check(ft_substr(str, start, i - start));
			node = make_node(split_str, ft_strlen(split_str), WORD, IN_DOUBLEQ);
			if (start - 1 >= 0 && str[start - 1] == '$')
				node->type = ENV;
			ft_add_back_list(l, node);
			start = -1;
		}
		if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			ft_add_back_list(l, make_node(ft_strdup("$"), 1, ENV, IN_DOUBLEQ));
		if (str[i] == ' ')
			ft_add_back_list(l, make_node(ft_strdup(" "), 1, SPC, NORMAL));
	}
}

t_node	*heredoc_expand_split(char *string, char ***env)
{
	char	*split_str;
	t_node	*exp_lst;
	t_node	*node;

	exp_lst = NULL;
	node = NULL;
	split_str = NULL;
	hd_make_node(string, &exp_lst, node, split_str);
	heredoc_expand_variable(&exp_lst, env, 0);
	return (exp_lst);
}
