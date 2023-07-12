/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/12 11:56:59 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_paris()
{
	char *line;

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
	line = ft_readline("minishell~>");
	// int fd = open("file1", O_RDWR);
	// printf("fd =%d errno: %s\n", fd, strerror(errno));
	// printf("hi\n");
	// printf("line = %s\n", line);
	return(0);
}
