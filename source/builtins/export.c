/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 13:23:53 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/07 19:45:40 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

char	**put_env(char *string, char ***env);
int		add_variable(char *string, char ***env);
int		check_variable(char **variable);

int	export_builtin(char **cmd_table, char ***env)
{
	int	i;
	int	j;
	int	val_set;

	i = 1;
	while (cmd_table[i])
	{
		if (!cmd_table[i])
		{
			j = 0;
			while ((*env)[j])
			{
				val_set = find_value((*env)[j]);
				if (val_set < 0)
					printf("declare -x %s\n", (*env)[j]);
				else
					printf("declare -x %.*s\"%s\"\n", val_set + 1, \
					(*env)[j], (*env)[j] + val_set + 1);
				i++;
			}
			return (0);
		}
		else
			add_variable(cmd_table[i], env);
		i++;
	}
	return (0);
}

int	add_variable(char *string, char ***env)
{
	char	*variable;
	int		join_value;
	int		val_set;

	if (!ft_isalpha(string[0]))
		error_exit("not a valid identifier", errno);
	if (find_value(string) < 0)
		return (0);
	variable = null_check(ft_substr(string, 0, find_value(string)));
	join_value = check_variable(&variable);
	val_set = find_env_var(variable, *env);
	if (val_set > 0 && join_value)
		(*env)[val_set] = null_check(ft_strjoin_free((*env)[val_set], \
		string + find_value(string) + 1));
	else if (val_set > 0)
	{
		free((*env)[val_set]);
		(*env)[val_set] = string;
	}
	else
		put_env(string, env);
	free(variable);
	return (0);
}

int	check_variable(char **variable)
{
	int	i;

	i = 0;
	while ((*variable)[i])
	{
		if ((*variable)[i + 1] == '\0' && (*variable)[i] == '+')
		{
			*variable = null_check(ft_strtrim_free(*variable, "+"));
			return (1);
		}
		else if (ft_isalnum((*variable)[i]))
			i++;
		else
			error_exit("not a valid identifier", errno);
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

char	**put_env(char *string, char ***env)
{
	int			i;
	char		**new_environ;

	new_environ = null_check(malloc (100 * sizeof(char *)));
	i = 0;
	while ((*env)[i])
	{
		new_environ[i] = (*env)[i];
		i++;
	}
	new_environ[i] = string;
	new_environ[i + 1] = NULL;
	free(*env);
	*env = new_environ;
	return (new_environ);
}
