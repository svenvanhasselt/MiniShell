/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 13:17:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/07 18:55:19 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <libft.h>
#include <minishell.h>

char	*strerror_minishell(int	error_no);
int		exit_status(int error_no);

void	*null_check(void *check)
{
	if (!check)
		error_exit("minishell failure", errno);
	return (check);
}

int	error_exit(char *message, int error_no)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror_minishell(error_no), 2);
	ft_putstr_fd("\n", 2);
	exit (exit_status(error_no));
}

void	error_seterrno(char *message, int error_no, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror_minishell(error_no), 2);
	ft_putstr_fd("\n", 2);
	status = exit_status(error_no);
}

char	*strerror_minishell(int	error_no)
{
	if (error_no == ERR_NO_CMD)
		return ("command not found");
	if (error_no == ERR_EXPORT_INVALID)
		return ("not a valid identifier");
	return (strerror(error_no));
}

int		exit_status(int error_no)
{
	if (error_no == EACCES)
		return(126);
	if (error_no == ERR_NO_CMD)
		return (127);
	return (1);
}