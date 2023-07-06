/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:30:06 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/06 16:56:30 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	copy_environ(int var_unset, char ***env);

int	unset_builtin(char *variable, char ***env)
{
	int			var_unset;
	
	if (!variable)
		return (0);
	var_unset = find_env_var(variable, *env);
	if (var_unset < 0)
		return (0);
	copy_environ(var_unset, env);
	return (0);
}

void	copy_environ(int var_unset, char ***env)
{
	int			i;
	int			j;
	char		**new_environ;

	new_environ = null_check(malloc (array_size(*env) * sizeof(char *)));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != var_unset)
			new_environ[j] = null_check(ft_strdup((*env)[i]));
		else
			j--;
		i++;
		j++;
	}
	new_environ[j] = NULL;
	i = 0;
	while ((*env)[i])
		free((*env)[i++]);
	free(*env);
	*env = new_environ;
}
