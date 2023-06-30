/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 10:44:18 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/30 11:52:19 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <minishell.h>

int	pwd(void)
{
	char *current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		error_exit("getcwd");
	if (printf("%s\n", current_dir) < 0)
		error_exit("pwd failure");
	free(current_dir);
	return (0);
}