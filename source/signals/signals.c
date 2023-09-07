/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:19:50 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/07 14:40:03 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <minishell.h>

void	signals_parent(void)
{
	hide_signals();
	if (signal(SIGINT, parent_signint) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
}

void	signals_child(void)
{
	show_signals();
	if (signal(SIGINT, child_sigint) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, child_sigquit) == SIG_ERR)
		error_exit("signal error", errno);
}

void	signals_heredoc(void)
{
	if (signal(SIGINT, heredoc_sigint) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, heredoc_sigint) == SIG_ERR)
		error_exit("signal error", errno);
}

void	signals_ignore(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
}
