/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:30:06 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/01 13:24:40 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	copy_environ(int var_unset);

int	unset(char *variable)
{
	int			var_unset;
	
	if (!variable)
		return (0);
	var_unset = find_env_var(variable);
	if (var_unset < 0)
		return (0);
	copy_environ(var_unset);
	return (0);
}

void	copy_environ(int var_unset)
{
	int			i;
	int			j;
	extern char	**environ;
	char		**new_environ;

	new_environ = null_check(malloc (array_size(environ) * sizeof(char *)));
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (i != var_unset)
			new_environ[j] = null_check(ft_strdup(environ[i]));
		else
			j--;
		i++;
		j++;
	}
	new_environ[j] = NULL;
	i = 0;
	while (environ[i])
		free(environ[i++]);
	free(environ);
	environ = new_environ;
}
