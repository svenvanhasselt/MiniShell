/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:06:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/24 16:15:26 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	syntax_error(t_node *tokens)
{
	int	rd_in_count;
	int	rd_out_count;

	rd_in_count = 0;
	rd_out_count = 0;
	if (tokens->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(404);
	}
	while(tokens != NULL)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL)
			{
				write(2, "sorry we can not handle this\n", 30);
				exit(3);
			}
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
		if (tokens->type == REDIRECT_OUT)
		{
			if (tokens->type == REDIRECT_OUT)
				rd_out_count++;
			printf("rd_out_count = %d\n", rd_out_count);
			printf("hiiiiiiii\n");
			printf("tokens->str = \"%s\" and type = %d and next = %p\n", tokens->str, tokens->type, tokens->next);
			while(tokens->next && tokens->next->type == SPACE && tokens->next != NULL)
			{
				printf("here  tokens->str = \"%s\" and type = %d\n", tokens->str, tokens->type);
				rd_out_count = 0;
				tokens = tokens->next;
			}
			printf("YEsssss\n");
			if (tokens->next && !(tokens->next->type == WORD ||\
			tokens->next->type == SINGLE_QOUTE || tokens->next->type == DOUBLE_QOUTE || tokens->next->type == REDIRECT_OUT))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
			if (tokens->next == NULL || rd_out_count > 2)
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
		}
		if (tokens->type == REDIRECT_IN)
		{
			if (tokens->type == REDIRECT_IN)
				rd_in_count++;
			printf("rd_in_count = %d\n", rd_in_count);
			printf("hiiiiiiii\n");
			printf("tokens->str = \"%s\" and type = %d and next = %p\n", tokens->str, tokens->type, tokens->next);
			while(tokens->next && tokens->next->type == SPACE && tokens->next != NULL)
			{
				printf("here  tokens->str = \"%s\" and type = %d\n", tokens->str, tokens->type);
				tokens = tokens->next;
			}
			printf("YEsssss\n");
			if (tokens->next && !(tokens->next->type == WORD ||\
			tokens->next->type == SINGLE_QOUTE || tokens->next->type == DOUBLE_QOUTE || tokens->next->type == REDIRECT_IN))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				exit(2);
			}
			if (tokens->next == NULL || rd_in_count > 2)
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