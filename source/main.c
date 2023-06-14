/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/14 18:26:22 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *line;

	while(1)
	{
		line = readline("minishell~> ");
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		else
			add_history(line);
	}
	printf("line = %s\n", line);
	return(0);
}
