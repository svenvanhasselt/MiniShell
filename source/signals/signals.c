/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:19:50 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/01 18:24:10 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <minishell.h>

void	signal_action_C_parent()
{
	unlink("here_doc");
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("test\n");
}

void	signal_action_quit_child()
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_init(void)
{
	if (signal(SIGINT, signal_action_C_parent) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
}

void	signals_default(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		error_exit("signal error", errno);
	
}
