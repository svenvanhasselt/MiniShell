/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:04:36 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/12 11:04:48 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd_in, int fd_out)
{
	if (fd_in != -5)
		close(fd_in);
	if (fd_out != -5)
		close(fd_out);
}
