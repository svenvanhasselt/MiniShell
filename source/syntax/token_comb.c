/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_comb.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 17:01:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/21 18:50:28 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	combine_tokens_utils(t_node *tokens, t_node *temp)
{
	tokens->str = ft_strjoin(tokens->str, tokens->next->str);
	tokens->len = ft_strlen(tokens->str);
	//tokens->state = IN_SINGLEQ;
	tokens->state = NORMAL;
	if (temp != NULL)
	{
		if (temp->next == NULL)
			tokens->next = NULL;
		else
		{
			tokens->next = tokens->next->next;
			temp->next = NULL;
		}
		free(temp->str);
		free(temp);
	}
	return ;
}

void	combine_tokens(t_node *tokens)
{
	t_node	*temp;

	temp = NULL;
	while (tokens)
	{
		if ((((tokens->state == IN_SINGLEQ || tokens->state == IN_DOUBLEQ) || (tokens->state == IN_DOUBLEQ && tokens->type == ENV)) && \
		((tokens->next && tokens->next->type == WORD) || (tokens->next && tokens->next->type == ENV	))) || \
		((tokens->state == NORMAL && tokens->type == WORD) && \
		(tokens->next && (tokens->next->state == IN_DOUBLEQ || \
		tokens->next->state == IN_SINGLEQ))))
		{
			temp = tokens->next;
			combine_tokens_utils(tokens, temp);
			if (temp == NULL)
			{
				free(temp->str);
				free(temp);
				tokens->next = NULL;
				break ;
			}
		}
		else
			tokens = tokens->next;
	}
}
