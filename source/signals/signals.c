/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:19:50 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/01 20:38:08 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <minishell.h>

extern int g_heredoc;

void	parent_signint(int sig)
{
	sig = 0;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	child_sigquit(int sig)
{
	sig = 0;
	printf("Quit: 3\n");
	signals_parent();
}

void	heredoc_signint(int sig)
{
	sig = 0;
	g_heredoc = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	signals_parent();
}

void	signals_parent(void)
{
	if (signal(SIGINT, parent_signint) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
}

void	signals_child(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, child_sigquit) == SIG_ERR)
		error_exit("signal error", errno);
	
}

void	signals_heredoc(void)
{
	if (signal(SIGINT, heredoc_signint) == SIG_ERR)
		error_exit("signal error", errno);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal error", errno);
	
}
