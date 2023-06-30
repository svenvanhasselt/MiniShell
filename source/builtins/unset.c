/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:30:06 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/30 12:56:23 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char *variable)
{
	int			i;
	int			var_unset;
	extern char **environ;
	char		**new_environ;

	var_unset = find_env_var(variable);
	if (var_unset < 0)
		return (0);
	i = 0;
	while (environ[i])
		i++;
	new_environ = null_check(malloc (i * sizeof(char *)));
	i = 0;
	while (environ[i])
	{
		if (i == var_unset)
		{
			i++;
			continue;
		}
		else
			new_environ[i] = null_check(ft_strdup(environ[i]));
		i++;
	}
	new_environ[i] = NULL;
	i = 0;
	while (environ[i])
		free(environ[i++]);
	free(environ);
	environ = new_environ;
	printf("%s\n", environ[4]);
	return (0);
}