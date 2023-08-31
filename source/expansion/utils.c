/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 16:35:32 by svan-has      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/08/31 16:41:37 by svan-has      ########   odam.nl         */
=======
/*   Updated: 2023/08/31 16:46:49 by svan-has      ########   odam.nl         */
>>>>>>> sven
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
	return (NULL);
}
