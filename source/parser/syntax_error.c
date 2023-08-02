/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:06:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/02 16:51:47 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	qoute_check(t_node *tokens)
{
	int	i;

	i = 0;
	if (tokens->str[i] == '\"')
	{
		i++;
		while(tokens->str[i] != '\0' && tokens->str[i] != '\"')
			i++;
		if (tokens->str[i] == '\0')
		{
			write(2, "Please close the double qoute!\n", 32);
			return (102);
		}
		else
			return (0);
	}
	else if (tokens->str[i] == '\'')
	{
		i++;
		while(tokens->str[i] != '\0' && tokens->str[i] != '\'')
			i++;
		if (tokens->str[i] == '\0')
		{
			write(2, "Please close the single qoute!\n", 32);
			return (101);
		}
		else
			return (0);
	}
	return (0);
}

int	syntax_error(t_node **tokens)
{
	int	rd_in_count;
	int	rd_out_count;
	int	qoute_result;
	t_node	*head;

	rd_in_count = 0;
	rd_out_count = 0;
	qoute_result = 0;
	head = *tokens;
	printf("we are in the syntax error function!\n");
	if (head->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		return (258);
	}
	while (head != NULL)
	{
		if (head->type == PIPE)
		{
			if (head->next == NULL)
			{
				write(2, "sorry we can not handle this\n", 30);
				return (100);
			}
			while (head->next->type == SPACE && head->next != NULL)
				head = head->next;
			if (!(head->next->type == WORD || head->next->type == SINGLE_QOUTE ||\
			head->next->type == DOUBLE_QOUTE))
			{
				write(2, "syntax error near unexpected token `|'\n", 40);
				return (258);
			}
		}
		//I am not sure about this syntax error and it needs more testing with bash
		if (head->type == REDIRECT_OUT)
		{
			if (head->type == REDIRECT_OUT)
				rd_out_count++;
			printf("rd_out_count = %d\n", rd_out_count);
			printf("head->str = \"%s\" and type = %d and next = %p\n", head->str, head->type, head->next);
			while (head->next && head->next->type == SPACE && head->next != NULL)
			{
				printf("here  head->str = \"%s\" and type = %d\n", head->str, head->type);
				rd_out_count = 0;
				head = head->next;
			}
			printf("YEsssss\n");
			if (head->next && !(head->next->type == WORD || head->next->type == SINGLE_QOUTE ||\
			head->next->type == DOUBLE_QOUTE || head->next->type == REDIRECT_OUT))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return (258);
			}
			if (head->next == NULL || rd_out_count > 2)
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return (258);
			}
		}
		if (head->type == REDIRECT_IN)
		{
			if (head->type == REDIRECT_IN)
				rd_in_count++;
			printf("rd_in_count = %d\n", rd_in_count);
			printf("head->str = \"%s\" and type = %d and next = %p\n", head->str, head->type, head->next);
			while (head->next && head->next->type == SPACE && head->next != NULL)
			{
				printf("here  head->str = \"%s\" and type = %d\n", head->str, head->type);
				head = head->next;
			}
			printf("YEsssss\n");
			if (head->next && !(head->next->type == WORD ||\
			head->next->type == SINGLE_QOUTE || head->next->type == DOUBLE_QOUTE || head->next->type == REDIRECT_IN))
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return (258);
			}
			if (head->next == NULL || rd_in_count > 2)
			{
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return (258);
			}
		}
		if (head->state == IN_DOUBLEQ || head->state == IN_SINGLEQ)
		{
			printf("and we found the qoute\n");
			qoute_result = qoute_check(head);
			if (qoute_result != 0)
				return(qoute_result);
		}
		head = head->next;
	}
	return (0);
}

// in this command "ls -l > | ls" my result is this = "syntax error near unexpected token `newline'\n" but bash result is this "syntax error near unexpected token `|'\n"
//why bash acts like this? I should find out and fix it