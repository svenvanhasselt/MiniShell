/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:30:06 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/12 13:43:34 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	copy_environ(int var_unset, char ***env);

int	unset_builtin(char **cmd_table, char ***env)
{
	int	i;
	int	var_unset;

	if (!cmd_table[1])
		return (0);
	i = 1;
	while (cmd_table[i])
	{
		var_unset = find_env_var(cmd_table[i], *env);
		if (var_unset < 0)
		{
			i++;
			continue ;
		}
		copy_environ(var_unset, env);
		i++;
	}
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
