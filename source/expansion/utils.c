/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:36:31 by svan-has          #+#    #+#             */
/*   Updated: 2023/08/08 09:30:57 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_word(t_node *head, char ***env, int *i)
{
	int		j;
	int		var_set;
	char	*variable;

	j = *i;
	while (head->str[j] && head->str[j] != ' ' && head->str[j] != '"')
		j++;
	variable = ft_substr(head->str, *i, j - *i);
	var_set = find_env_var(variable, (*env));
	free(variable);
	*i = j;
	if (var_set >= 0)
		return (ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
	return (NULL);
}

int	find_len(t_node *head, char ***env, int *i)
{
	int		j;
	int		var_set;
	char	*variable;

	j = *i;
	while (head->str[j] && head->str[j] != ' ' && head->str[j] != '"')
		j++;
	variable = ft_substr(head->str, *i, j - *i);
	var_set = find_env_var(variable, (*env));
	free(variable);
	*i = j;
	if (var_set >= 0)
		return (ft_strlen((*env)[var_set] + find_value((*env)[var_set]) + 1));
	return (0);
}

int	new_length(t_node *head, char ***env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (head->str[i])
	{
		if (head->str[i] == '$')
		{
			i++;
			len += find_len(head, env, &i);
		}
		i++;
		len++;
	}
	return (len);
}

void	copy_variable(char **new_str, char *variable, int *j)
{
	int		k;

	k = 0;
	while (variable && variable[k])
	{
		(*new_str)[*j] = variable[k];
		(*j)++;
		k++;
	}
	free(variable);
}
