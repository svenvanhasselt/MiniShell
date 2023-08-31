/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 17:02:38 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand(t_node *head, t_node	**node)
{
	if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
		*node = split_variable(head);
}

void	expand_exit_code(t_node *head, int exit_status)
{
	free(head->str);
	head->str = null_check((ft_itoa(exit_status)));
}

void	expand_variable(t_node **lst, char ***env, int exit_status)
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
			{
				expand_exit_code(head, exit_status);
				continue ;
			}
			head->str = find_variable(head->str, head->type, env);
			if (*lst == head)
				expand(head, lst);
			else
				expand(head, &prev);
		}
		prev = head;
		head = head->next;
	}
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;
	t_node	*prev;
	t_node	*current;

	head = *lst;
	prev = *lst;
	while (head)
	{
		if (head->type == ENV || (head->state == IN_DOUBLEQ && \
		ft_strnstr(head->str, "$", head->len)))
		{
			current = head;
			if (head->state == IN_DOUBLEQ)
				head->str = ft_strtrim_free(head->str, "\"");
			if (*lst == head)
				*lst = expand_split(&head, env, exit_status);
			else
				prev->next = expand_split(&head, env, exit_status);
			free(current->str);
			free(current);
		}
		prev = head;
		head = head->next;
	}
}
