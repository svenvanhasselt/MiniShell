/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 14:06:37 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/09 19:38:29 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_pipe(t_node **head)
{
	if ((*head)->next == NULL)
	{
		write(2, "sorry we can not handle this\n", 30);
		return (100);
	}
	while ((*head)->next->type == SPACE && (*head)->next != NULL)
		(*head) = (*head)->next;
	if (!((*head)->next->type == WORD || \
	(*head)->next->type == SINGLE_QOUTE || \
	(*head)->next->type == DOUBLE_QOUTE))
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		return (258);
	}
	return (0);
}

int	syntax_rd_out(t_node **h)
{
	if ((*h)->next && (*h)->next->type == SPACE)
	{
		while ((*h)->next && (*h)->next->type == SPACE && (*h)->next != NULL)
			(*h) = (*h)->next;
		if ((*h)->next->type == REDIRECT_IN || (*h)->next->type == REDIRECT_OUT)
		{
			write(2, "syntax error near unexpected token `>'\n", 40);
			return (258);
		}
	}
	if ((*h)->next && (*h)->next->next && \
	(*h)->next->type == REDIRECT_OUT && (*h)->next->next->type == REDIRECT_OUT)
	{
		write(2, "syntax error near unexpected token `>'\n", 40);
		return (258);
	}
	if ((*h)->next && !((*h)->next->type == WORD || \
	(*h)->next->type == SINGLE_QOUTE || (*h)->next->type == DOUBLE_QOUTE \
	|| (*h)->next->type == REDIRECT_OUT))
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		return (258);
	}
	return (0);
}

int	syntax_rd_in(t_node **h)
{
	if ((*h)->next && (*h)->next->type == SPACE)
	{
		while ((*h)->next && (*h)->next->type == SPACE && (*h)->next != NULL)
			(*h) = (*h)->next;
		if ((*h)->next->type == REDIRECT_IN || (*h)->next->type == REDIRECT_OUT)
		{
			write(2, "syntax error near unexpected token `<'\n", 40);
			return (258);
		}
	}
	if ((*h)->next && !((*h)->next->type == WORD || \
	(*h)->next->type == SINGLE_QOUTE || (*h)->next->type == \
	DOUBLE_QOUTE || (*h)->next->type == REDIRECT_IN))
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		return (258);
	}
	if ((*h)->next && (*h)->next->next && (*h)->next->type == \
	REDIRECT_OUT && (*h)->next->next->type == REDIRECT_OUT)
	{
		write(2, "syntax error near unexpected token `<'\n", 40);
		return (258);
	}
	return (0);
}

int	syntax_head(t_node *head)
{
	if (head->type == PIPE)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		return (258);
	}
	if (head->next == NULL && (head->type == REDIRECT_IN \
	|| head->type == REDIRECT_OUT))
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		return (258);
	}
	return (0);
}

int	syntax_error(t_node **tokens)
{
	t_node	*head;
	int		exit_code;

	head = *tokens;
	exit_code = syntax_head(head);
	if (exit_code != 0)
		return (exit_code);
	while (head != NULL)
	{
		if (head->type == PIPE)
			exit_code = syntax_pipe(&head);
		else if (head->type == REDIRECT_OUT)
			exit_code = syntax_rd_out(&head);
		else if (head->type == REDIRECT_IN)
			exit_code = syntax_rd_in(&head);
		else if (head->state == IN_DOUBLEQ || head->state == IN_SINGLEQ)
			exit_code = qoute_check(head);
		if (exit_code != 0)
			return (exit_code);
		head = head->next;
	}
	return (0);
}
