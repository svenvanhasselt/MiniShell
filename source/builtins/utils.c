/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/06 18:19:20 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/06 18:28:09 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(char ***env)
{
	int	i;
	int	val_set;

	i = 0;
	while ((*env)[i])
	{
		val_set = find_value((*env)[i]);
		if (val_set < 0)
			printf("declare -x %s\n", (*env)[i]);
		else
			printf("declare -x %.*s\"%s\"\n", val_set + 1, \
			(*env)[i], (*env)[i] + val_set + 1);
		i++;
	}
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
