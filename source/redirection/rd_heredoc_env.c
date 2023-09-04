/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 13:54:56 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/04 13:55:40 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_find_env_var(char *variable, char **env)
{
	int			i;
	char		*new_variable;
	char		*after_trim;

	after_trim = ft_strtrim(variable, "\n");
	new_variable = ft_strjoin(after_trim, "=");
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], new_variable, ft_strlen(new_variable)) || \
		!strncmp(env[i], after_trim, ft_strlen(after_trim)))
			return (free(new_variable), free(after_trim), i);
		i++;
	}
	free(after_trim);
	free(new_variable);
	return (-1);
}

char	*heredoc_find_variable(char *variable, enum e_token type, char ***env)
{
	int		var_set;
	char	*value;
	int		len;

	len = ft_strlen(variable);
	var_set = heredoc_find_env_var(variable, (*env));
	if (var_set >= 0)
	{
		value = null_check(ft_strdup(((*env)[var_set] + \
		find_value((*env)[var_set]) + 1)));
		if (variable[len - 1] == '\n')
			value = ft_strjoin_free(value, "\n");
		free(variable);
		return (value);
	}
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (variable);
	else if (type == EXP)
		return (NULL);
	return (NULL);
}
