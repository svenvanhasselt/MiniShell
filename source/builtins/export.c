/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 13:23:53 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/04 18:41:31 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**put_env(char *string, char **env);

int	export(char *string, char **env)
{
	int			i;
	int			val_set;
	char		*value;

	if (!string)
	{
		i = 0;
		while (env[i])
		{
			val_set = find_value(env[i]);
			if (val_set < 0)
				printf("declare -x %s\n", env[i]);
			else
				printf("declare -x %.*s\"%s\"\n", val_set+1, env[i], env[i] + val_set +1);
			i++;
		}
		return (0);
	}
	else
	{
		value = null_check(ft_substr(string, 0, find_value(string)));
		val_set = find_env_var(value, env);
		if (val_set > 0)
		{
			if (find_value(string) < 0)
				return (free(value), 0);
			free(env[val_set]);
			env[val_set] = string;
		}
		else
			env = put_env(string, env);
		free(value);
	}
	env_builtin(env);
	return (0);
}

int	find_value(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**put_env(char *string, char **env)
{
	int			i;
	char		**new_environ;

	new_environ = null_check(malloc ((array_size(env)+2) * sizeof(char *)));
	i = 0;
	while (env[i])
	{
		new_environ[i] = env[i];
		i++;
	}
	new_environ[i] = string;
	new_environ[i + 1] = NULL;
	// free(env);
	return (new_environ);
}