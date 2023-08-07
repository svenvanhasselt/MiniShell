/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:26:09 by svan-has          #+#    #+#             */
/*   Updated: 2023/08/07 17:44:57 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_word(t_node *head, char ***env, int exit_status)
{
	int	i;
	int	var_set;

	if (ft_strncmp(head->str, "$?", 2) == 0)
	{
		free(head->str);
		head->str = ft_strdup(ft_itoa(exit_status));
	}
	else
	{
		var_set = find_env_var((head->str + 1), (*env));
		if (var_set < 0)
		{
			free(head->str);
			head->str = ft_strdup("");
		}
		else
		{
			free(head->str);
			i = find_value((*env)[var_set]);
			head->str = ft_strdup((*env)[var_set] + i + 1);
		}
	}
}

char	*new_str(t_node *head, char ***env, int len, int exit_status)
{
	int		i;
	int		j;
	char	*new_str;
	char	*variable;

	new_str = null_check(malloc((len + 1) * sizeof(char)));
	i = 0;
	j = 0;
	while (head->str[i])
	{
		if (head->str[i] == '$')
		{
			i++;
			variable = find_word(head, env, &i);
			copy_variable(&new_str, variable, &j);
		}
		else
		{
			new_str[j] = head->str[i];
			j++;
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

void	expand_quotes(t_node *head, char ***env, int exit_status)
{
	// free(head->str);
	head->str = new_str(head, env, new_length(head, env), exit_status); // LEAKES?
	// Is there a leak??
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;

	head = *lst;
	while (head)
	{
		if (head->type == ENV)
			expand_word(head, env, exit_status);
		else if (head->state == 2)
			expand_quotes(head, env, exit_status);
		head = head->next;
	}
}
