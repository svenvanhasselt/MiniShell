/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 13:17:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/23 12:04:47 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <libft.h>
#include <minishell.h>

char	*strerror_minishell(int error_no);
int		exit_status(int error_no);

void	*null_check(void *check)
{
	if (!check)
		error_exit("operation failure", errno);
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

int	error_seterrno(char *message, char *message2, int error_no)
{
	ft_putstr_fd("minishell: ", 2);
	if (message)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message2)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(message2, 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror_minishell(error_no), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

char	*strerror_minishell(int error_no)
{
	if (error_no == ERR_NO_CMD)
		return ("command not found");
	if (error_no == ERR_EXPORT_INVALID)
		return ("not a valid identifier");
	if (error_no == ERR_CD_FILE_UNAIV)
		return ("No such file or directory");
	if (error_no == ERR_CD_NO_HOME)
		return ("HOME not set");
	if (error_no == ERR_CD_NOT_DIR)
		return ("Not a directory");
	if (error_no == ERR_EXIT_ARG)
		return ("too many arguments");
	if (error_no == ERR_EXIT_NUM)
		return ("numeric argument required");
	return (strerror(error_no));
}

int	exit_status(int error_no)
{
	if (error_no == EACCES)
		return (126);
	if (error_no == ERR_NO_CMD)
		return (127);
	return (1);
}
