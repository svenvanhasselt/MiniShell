/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 13:17:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/06/29 13:21:25 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void *null_check(void *check)
{
	if (!check)
		exit (write(2, "minishell failure\n", 18));
	return (check);
}