/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 19:53:13 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/08 14:33:07 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	child_sigint(int sig)
{
	sig = 0;
	printf("\n");
	return ;
}

void	heredoc_sigint(int sig)
{
	printf("\n");
	exit (sig);
}
