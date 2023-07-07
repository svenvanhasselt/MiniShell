/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:04:19 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/07 19:45:13 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_dir(char *path, char ***env);

int	cd_builtin(char **cmd_table, char ***env)
{
	if ((!cmd_table[1] && !getenv("HOME")) || \
	(cmd_table[1] && !ft_strncmp(cmd_table[1], "", 1)))
		return (0);
	else if (!cmd_table[1] && change_dir((getenv("HOME")), env) > 0)
		return (1);
	else if (cmd_table[1] && change_dir((cmd_table[1]), env) > 0)
		return (2);
	return (0);
}

int	find_env_var(char *variable, char **env)
{
	int			i;
	char		*new_variable;

	new_variable = ft_strjoin(variable, "=");
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], new_variable, ft_strlen(new_variable)))
			return (free(new_variable), i);
		i++;
	}
	free(new_variable);
	return (-1);
}

int	change_dir(char *path, char ***env)
{
	int			env_pwd;
	int			env_oldpwd;
	char		*old_dir;
	char		*new_dir;

	env_pwd = find_env_var("PWD", *env);
	env_oldpwd = find_env_var("OLDPWD", *env);
	old_dir = null_check(getcwd(NULL, 0));
	if (chdir(path) < 0)
		error_exit(path, errno);
	new_dir = null_check(getcwd(NULL, 0));
	export_builtin(null_check(ft_strjoin("PWD=", new_dir)), env);
	export_builtin(null_check(ft_strjoin("OLDPWD=", old_dir)), env);
	free(old_dir);
	free(new_dir);
	return (0);
}
