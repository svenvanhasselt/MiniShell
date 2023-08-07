/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/03 15:03:49 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_word(t_node *head, char ***env)
{
	int	i;
	int	var_set;

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

char	*new_str(t_node *head, char ***env, int len)
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

void	expand_quotes(t_node *head, char ***env)
{
	// free(head->str);
	head->str = new_str(head, env, new_length(head, env));
	// Is there a leak??
}

void	expansion(t_node **lst, char ***env)
{
	t_node	*head;

	head = *lst;
	while (head)
	{
		if (head->type == ENV)
			expand_word(head, env);
		else if (head->state == 2)
			expand_quotes(head, env);
		head = head->next;
	}
}
