/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 18:30:32 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/23 12:42:11 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minishell.h>

int	exit_builtin(char **cmd_table, int status)
{
	int	i;
	int	arr_size;

	printf("exit\n");
	arr_size = array_size(cmd_table);
	if (arr_size > 2)
		return (error_seterrno(cmd_table[0], NULL, ERR_EXIT_ARG));
	else if (arr_size == 2)
	{
		i = 0;
		while (cmd_table[1][i])
		{
			if (ft_isdigit(cmd_table[1][i]))
				i++;
			else
			{
				error_seterrno(cmd_table[0], cmd_table[1], ERR_EXIT_NUM);
				exit (255);
			}
		}
		exit (ft_atoi(cmd_table[1]));
	}
	exit(status);
}
