/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:03 by psadeghi          #+#    #+#             */
/*   Updated: 2023/07/25 06:57:38 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
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
