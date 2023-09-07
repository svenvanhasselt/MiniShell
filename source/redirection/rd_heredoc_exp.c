/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc_exp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 13:16:27 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/05 13:30:35 by psadeghi      ########   odam.nl         */
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

t_node	*heredoc_expand_split(char *string, char ***env)
{
	t_node	*exp_lst;

	exp_lst = NULL;
	split_string(string, &exp_lst);
	heredoc_expand_variable(&exp_lst, env, 0);
	return (exp_lst);
}
