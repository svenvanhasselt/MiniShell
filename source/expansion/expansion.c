/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 16:17:20 by svan-has      ########   odam.nl         */
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

void	expand_variable(t_node **lst, char ***env, int exit_status)
{	
	t_node	*head;
	t_node	*prev;
	t_node	*current;

	head = *lst;
	prev = head;
	while (head)
	{
		current = head;
		if (head->type == ENV)
		{
			if (!ft_strncmp(head->str, "?", ft_strlen(head->str)))
			{
				free(head->str);
				head->str = null_check((ft_itoa(exit_status)));
			}
			else if (*lst == head)
			{
				head->str = find_variable(head->str, head->type, env);
				if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
				{
					*lst = split_variable(head);
					// free(current);
				}
			}
			else
			{
				head->str = find_variable(head->str, head->type, env);
				if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
					prev = split_variable(head);
			}
		}
		prev = head;
		head = head->next;
	}
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;
	t_node  *prev;
	t_node	*current;

	head = *lst;
	prev = *lst;
	while (head)
	{
		if (head->type == ENV || (head->state == IN_DOUBLEQ && ft_strnstr(head->str, "$", head->len)))
		{
			current = head;
			if (head->state == IN_DOUBLEQ)
				head->str = ft_strtrim_free(head->str, "\"");
			if (*lst == head)
			{
				*lst = expand_split(&head, env, exit_status);
				free(current->str);
				free(current);
			}
			else
			{
				prev->next = expand_split(&head, env, exit_status);
				free(current->str);
				free(current);
			}				
		}
		prev = head;
		head = head->next;
	}
}
