/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:19:50 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/04 13:14:33 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>

void	signal_action(int signum)
{
	ft_putstr_fd("Waiting...", 2);
	sleep(5);
	printf("Caught this signal: %d\n", signum);
	write(2, "Here!\n", 6);
	pid_t pid = getpid();
	printf("pid: %d\n", pid);
	exit(1);
}

void		signals_init(void)
{
	signal(SIGINT, signal_action); // Diplay new prompt on new line CTRL-C
	signal(SIGQUIT, SIG_IGN); // Do nothing CTRL-'\'
}
