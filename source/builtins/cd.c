/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:04:19 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/28 12:28:26 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var(char *variable);
int	change_dir(char *path);
char **ft_putenv(char *variable, char *path);

int	cd(char **cmd_table)
{
	extern char **environ;

	printf("PWD:  %s\n", getenv("PWD"));
	printf("OLDPWD:  %s\n", getenv("OLDPWD"));
	printf ("%d\n", change_dir(".."));
	printf("PWD:  %s\n", getenv("PWD"));
	printf("OLDPWD:  %s\n", getenv("OLDPWD"));
	// // env_var = find_env_var("PWD=");
	// system("pwd");
	// printf("PWD:  %s\n", getenv("PWD"));
	// if (!cmd_table[1] && !getenv("HOME"))
	// 	return (0);
	// else if (!cmd_table[1] && chdir(getenv("HOME")) < 0)
	// 	return (1);
	// else if (cmd_table[1] && chdir(cmd_table[1]) < 0)
	// 	return (2);
	// system("pwd");	
	// printf("PWD: %s\n", getenv("PWD"));
	
	
	
	return (0);
}

int	find_env_var(char *variable)
{
	int			i;
	extern char **environ;

	i = 0;
	while(environ[i])
	{
		if (!strncmp(environ[i], variable, ft_strlen(variable)))
			return (i);
		i++;
	}
	return (-1);
}

int	change_dir(char *path)
{
	int			env_pwd;
	int			env_oldpwd;
	char		*old_dir;
	char		*new_dir;
	extern char **environ;

	env_pwd = find_env_var("PWD=");
	env_oldpwd = find_env_var("OLDPWD=");
	old_dir = getcwd(NULL, 0);
	if (!old_dir)
		return (1);
	if (chdir(path) < 0)
		return (1);
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
		return (1);
	if (env_pwd >= 0)
		environ[env_pwd] = new_dir;
	else
		printf("Create new array\n");
	if (env_oldpwd >= 0)
		environ[env_oldpwd] = old_dir;
	else
		printf("Create new array\n");
	return (0);
}

char **ft_putenv(char *variable, char *path)
{
	int			i;
	extern char **environ;
	char		**new_environ;

	env_len = 0;
	while(environ[i])
		i++;
	new_environ = malloc ((i + 2) * sizeof(char *));
	if (!new_environ)
		return (1);
	i = -1;
	while (environ[i++])
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
			return (1);
		i++;
	}
	new_environ[i] = ft_strjoin(variable, path);
	if (!new_environ[i])
		return (1);
	new_environ[i + 1] = NULL;
	return (new_environ);
}