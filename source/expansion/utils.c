/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 12:36:31 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/15 17:19:32 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_word(char *string, char ***env, int *i)
{
	int		j;
	int		var_set;
	char	*variable;

	j = *i;
	while (string[j] && string[j] != ' ' && string[j] != '"' && string[j] != '$')
		j++;
	variable = ft_substr(string, *i, j - *i);
	var_set = find_env_var(variable, (*env));
	free(variable);
	*i = j;
	if (var_set >= 0)
		return (ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
	return (NULL);
}

char	*find_variable(char *variable, char ***env)
{
	int		var_set;
	char	*value;

	var_set = find_env_var(variable, (*env));
	free(variable);
	if (var_set >= 0)
	{
		value = null_check(ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
		return (value);
	}
	return (null_check(ft_strdup("")));
}

char	**split_variable(char *string, char ***env, int exit_status)
{
	int	i;
	char **split_str;

	split_str = null_check(ft_split(string, '$'));
	i = 0;
	while (split_str[i])
	{
		if (!ft_strncmp(split_str[i], "?", ft_strlen(split_str[i])))
		{
			free(split_str[i]);
			split_str[i] = null_check(ft_strdup(null_check(ft_itoa(exit_status))));
		}
		else
			split_str[i] = find_variable(split_str[i], env);
		i++;
	}
	return (split_str);
}