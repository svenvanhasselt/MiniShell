/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:04:19 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/03 12:07:30 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_env_var(char *variable);
int		change_dir(char *path);

int	cd(char **cmd_table)
{
	if ((!cmd_table[1] && !getenv("HOME")) || \
	(cmd_table[1] && !ft_strncmp(cmd_table[1], "", 1)))
		return (0);
	else if (!cmd_table[1] && change_dir((getenv("HOME"))) > 0)
		return (1);
	else if (cmd_table[1] && change_dir((cmd_table[1])) > 0)
		return (2);
	return (0);
}

int	find_env_var(char *variable)
{
	int			i;
	extern char	**environ;
	char		*new_variable;

	new_variable = ft_strjoin(variable, "=");
	i = 0;
	while (environ[i])
	{
		if (!strncmp(environ[i], new_variable, ft_strlen(new_variable)))
			return (free(new_variable), i);
		i++;
	}
	free(new_variable);
	return (-1);
}

int	change_dir(char *path)
{
	int			env_pwd;
	int			env_oldpwd;
	char		*old_dir;
	char		*new_dir;
	extern char	**environ;

	env_pwd = find_env_var("PWD");
	env_oldpwd = find_env_var("OLDPWD");
	old_dir = null_check(getcwd(NULL, 0));
	if (chdir(path) < 0)
		return (2);
	new_dir = null_check(getcwd(NULL, 0));
	export(null_check(ft_strjoin("PWD=", new_dir)));
	export(null_check(ft_strjoin("OLDPWD=", old_dir)));
	free(old_dir);
	free(new_dir);
	return (0);
}
