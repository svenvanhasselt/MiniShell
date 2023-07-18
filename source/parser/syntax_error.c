/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:06:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/18 17:28:32 by psadeghi      ########   odam.nl         */
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
	while(tokens != NULL)
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
			printf("hiiiiiiii\n");
			printf("tokens->str = \"%s\" and type = %d and next = %p\n", tokens->str, tokens->type, tokens->next);
			while(tokens->next && tokens->next->type == SPACE && tokens->next != NULL)
			{
				printf("here  tokens->str = \"%s\" and type = %d\n", tokens->str, tokens->type);
				tokens = tokens->next;
			}
			printf("YEsssss\n");
			if (tokens->next && !(tokens->next->type == WORD ||\
			tokens->next->type == SINGLE_QOUTE || tokens->next->type == DOUBLE_QOUTE))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
			if (tokens->next == NULL)
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
		}
		tokens = tokens->next;
	}
}

// in this command "ls -l > | ls" my result is this = "syntax error near unexpected token `newline'\n" but bash result is this "syntax error near unexpected token `|'\n"
//why bash acts like this? I should find out and fix it