/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 12:08:54 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/30 12:12:46 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

int	env(void)
{
	int			i;
	extern char **environ;

	i = 0;
	while (environ[i])
	{
		if (printf("%s\n", environ[i]) < 0)
			error_exit("env failure");
		i++;
	}
	return (0);
}