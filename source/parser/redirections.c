/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 15:00:33 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/12 17:04:20 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rd_managment(t_node *tokens, t_parser_list **p_list)
{
	t_parser_list	*node;

	if (tokens->type == REDIRECT_OUT)
	{
		printf("yesssss\n");
		tokens = tokens->next;
		if (!(tokens->type == SPACE || tokens->type == WORD))
		{
			write(2, "syntax error near unexpected token `newline'\n", 46);
			exit(2);
		}
		while(tokens->type == SPACE && tokens->type != PIPE && tokens->next != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
		if (tokens->type == PIPE)
		{
			write(2, "syntax error near unexpected token `|'\n", 40);
			exit(3);
		}
		printf("after the space? = %s\n", tokens->str);
		if (tokens->type == WORD)
		{
			node = ft_lastlist_lparser(*p_list);
			node->rd_out = true;
			node->file_out = tokens->str;
			node->fd_out = open(tokens->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (node->fd_out == -1)
			{
				node->errno_out = errno;
				printf("this is errno = %d\n", errno);
			}
			if (tokens->next != NULL)
				tokens = tokens->next;
		}
		while(tokens->type == SPACE && tokens->next != NULL)
		{
			printf("i\n");
			tokens = tokens->next;
		}
	}
	return(tokens);
}
