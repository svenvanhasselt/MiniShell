/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termios.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/06 15:53:12 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/07 15:08:08 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>

void	hide_signals(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		error_exit("operation failure", errno);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	show_signals(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		error_exit("operation failure", errno);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		error_exit("operation failure", errno);
}
