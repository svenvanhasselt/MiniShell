/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/04 18:25:28 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(void)
{
	system("leaks -quiet minishell");
}

int	main()
{
	// char *line;

	atexit(f);
	execution();
	// while(1)
	// {
	// 	line = readline("minishell~> ");
	// 	if (!line)
	// 	{
	// 		printf("exit\n");
	// 		exit(1);
	// 	}
	// 	else
	// 		add_history(line);
	// }
	// printf("line = %s\n", line);
	exit (0);
	return(0);
}
