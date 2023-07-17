/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:06:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/17 17:08:44 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	syntax_error(t_node *tokens)
{
	if (tokens->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(404);
	}
	while(tokens->next != NULL)
	{
		if (tokens->type == PIPE)
		{
			while(tokens->next->type == SPACE && tokens->next != NULL)
				tokens = tokens->next;
			if (!(tokens->next->type == WORD ||\
			tokens->next->type == SINGLE_QOUTE || tokens->next->type == DOUBLE_QOUTE))
			{
				write(2, "syntax error near unexpected token `|'\n", 40);
				exit(2);
			}
		}
		//I am not sure about this syntax error and it needs more testing with bash
		if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT)
		{
			while(tokens->next->type == SPACE && tokens->next != NULL)
				tokens = tokens->next;
			if (!(tokens->next->type == WORD ||\
			tokens->next->type == SINGLE_QOUTE || tokens->next->type == DOUBLE_QOUTE))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
		}
		tokens = tokens->next;
	}
	printf("it's not here\n");
}

// in this command "ls -l > | ls" my result is this = "syntax error near unexpected token `newline'\n" but bash result is this "syntax error near unexpected token `|'\n"
//why bash acts like this? I should find out and fix it