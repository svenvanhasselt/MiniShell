/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 13:23:53 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/08 14:41:48 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void	put_env(char *string, char ***env);
int		add_variable(char *string, char ***env);
int		check_variable(char **variable);

int	export_builtin(char **cmd_table, char ***env)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (!cmd_table[1])
	{
		print_env(env);
		return (0);
	}
	i = 1;
	while (cmd_table[i])
	{
		if (add_variable(cmd_table[i], env) < 0)
			exit_code = error_seterrno(cmd_table[0], \
			cmd_table[i], ERR_EXPORT_INVALID);
		i++;
	}
	return (exit_code);
}

int	syntax_check(char *string)
{
	int	i;

	if (string && !ft_isalpha(string[0]))
		return (-1);
	i = 1;
	while (string && string[i] && string[i] != '=')
	{
		if (!ft_isalnum(string[i]) && string[i] != '+')
			return (-1);
		i++;
	}
	return (0);
}

int	add_variable(char *string, char ***env)
{
	char	*variable;
	int		join_value;
	int		val_set;

	if (syntax_check(string) < 0)
		return (-1);
	variable = null_check(ft_substr(string, 0, find_value(string)));
	join_value = check_variable(&variable);
	if (join_value < 0)
		return (-1);
	val_set = find_env_var(variable, *env);
	if (val_set > 0 && join_value)
		(*env)[val_set] = null_check(ft_strjoin_free((*env)[val_set], \
		string + find_value(string) + 1));
	else if (val_set > 0)
	{
		free((*env)[val_set]);
		(*env)[val_set] = null_check(ft_strdup(string));
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
		i++;
	}
	return (0);
}

void	put_env(char *string, char ***env)
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
	new_environ[i] = null_check(ft_strdup(string));
	new_environ[i + 1] = NULL;
	free(*env);
	*env = new_environ;
}
