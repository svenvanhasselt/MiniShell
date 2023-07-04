/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:08:54 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/04 18:35:25 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_builtin(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (printf("%s\n", env[i]) < 0)
			error_exit("env failure");
		i++;
	}
	return (0);
}
