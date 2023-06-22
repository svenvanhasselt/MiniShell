/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:04:19 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/22 15:12:02 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **cmd_table)
{
	char *current_dir;

	current_dir = NULL;
	current_dir = getcwd(current_dir, 0);
	system("pwd");
	if (!cmd_table[1] && chdir(getenv("HOME")) < 0)
		return (1);
	if (chdir(cmd_table[1]) < 0)
		return (1);
	system("pwd");
	return (0);
}