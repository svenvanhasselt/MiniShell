/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 13:23:53 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/03 17:32:39 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_value(char *string);
int	putenv(char *string);

int	export(char *string)
{
	int			i;
	int			val_set;
	char		*value;
	extern char	**environ;

	if (!string)
	{
		i = 0;
		while (environ[i])
		{
			val_set = find_value(environ[i]);
			if (val_set < 0)
				printf("declare -x %s\n", environ[i]);
			else
				printf("declare -x %.*s\"%s\"\n", val_set+1, environ[i], environ[i] + val_set +1);
			i++;
		}
		return (0);
	}
	else
	{
		value = null_check(ft_substr(string, 0, find_value(string)));
		val_set = find_env_var(value);
		if (val_set > 0)
		{
			if (find_value(string) < 0)
				return (free(value), 0);
			free(environ[val_set]);
			environ[val_set] = string;
		}
		else
			putenv(string);
		free(value);
	}
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

int	putenv(char *string)
{
	int			i;
	extern char	**environ;
	char		**new_environ;

	new_environ = null_check(malloc ((array_size(environ)+2) * sizeof(char *)));
	i = 0;
	while (environ[i])
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[i] = string;
	new_environ[i + 1] = NULL;
	free(environ);
	environ = new_environ;
	return (0);
}