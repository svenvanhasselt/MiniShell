/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc_exp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 13:16:27 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/08 10:25:20 by psadeghi      ########   odam.nl         */
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

void	heredoc_add_exp_list(t_node *prev, t_node *head, char ***env)
{
	prev->next = heredoc_expand_split(&head, env);
	prev = prev->next;
}

void	heredoc_expansion(t_node **lst, char ***env)
{
	t_node	*head;
	t_node	*prev;
	t_node	*next;

	head = *lst;
	prev = *lst;
	while (head)
	{
		next = head->next;
		if (head->type == ENV || (head->state == IN_DOUBLEQ && \
		ft_strnstr(head->str, "$", head->len)) || (head->state == \
		IN_SINGLEQ && ft_strnstr(head->str, "$", head->len)))
		{
			if (*lst == head)
				*lst = heredoc_expand_split(&head, env);
			else
				heredoc_add_exp_list(prev, head, env);
			free(head->str);
			free(head);
		}
		else
			prev = head;
		head = next;
	}
}
