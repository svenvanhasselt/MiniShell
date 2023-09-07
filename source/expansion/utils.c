/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 16:35:32 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/07 14:32:36 by svan-has      ########   odam.nl         */
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
		value = null_check(ft_strdup(((*env)[var_set] + \
		find_value((*env)[var_set]) + 1)));
		free(variable);
		return (value);
	}
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (variable);
	else if (type == EXP)
		return (NULL);
	return (free(variable), NULL);
}
