/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:04:19 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/06 19:12:15 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int		change_dir(char *path, char ***env);
int		add_variable_cd(char *string, char ***env);

int	cd_builtin(char **cmd_table, char ***env)
{
	struct stat	path_stat;

	if (cmd_table[1] && stat(cmd_table[1], &path_stat) > 0)
		error_exit("operation failure", errno);
	if ((!cmd_table[1] && !getenv("HOME")))
		return (error_seterrno(cmd_table[0], NULL, ERR_CD_NO_HOME));
	else if (cmd_table[1] && !ft_strncmp(cmd_table[1], "", 1))
		return (0);
	else if (!cmd_table[1] && change_dir((getenv("HOME")), env) < 0)
		return (error_seterrno(cmd_table[0], NULL, ERR_CD_NO_HOME));
	else if (cmd_table[1] && S_ISREG(path_stat.st_mode))
		return (error_seterrno(cmd_table[0], cmd_table[1], ERR_CD_NOT_DIR));
	else if (cmd_table[1] && change_dir((cmd_table[1]), env) < 0)
		return (error_seterrno(cmd_table[0], cmd_table[1], ERR_CD_FILE_UNAIV));
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
		if (!strncmp(env[i], new_variable, ft_strlen(new_variable)) || \
		!strncmp(env[i], variable, ft_strlen(variable)))
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
		return (free(old_dir), -1);
	new_dir = null_check(getcwd(NULL, 0));
	add_variable_cd(null_check(ft_strjoin("PWD=", new_dir)), env);
	add_variable_cd(null_check(ft_strjoin("OLDPWD=", old_dir)), env);
	free(old_dir);
	free(new_dir);
	return (0);
}

int	add_variable_cd(char *string, char ***env)
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
	free(string);
	return (0);
}
