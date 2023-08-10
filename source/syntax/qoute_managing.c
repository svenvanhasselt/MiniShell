/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   qoute_managing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:58:19 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/10 14:29:02 by psadeghi      ########   odam.nl         */
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
		while (tokens->str[i] != '\0' && tokens->str[i] != '\"')
			i++;
		if (tokens->str[i] == '\0')
			return (write(2, "Please close the double qoute!\n", 32), 102);
	}
	else if (tokens->str[i] == '\'')
	{
		i++;
		while (tokens->str[i] != '\0' && tokens->str[i] != '\'')
			i++;
		if (tokens->str[i] == '\0')
			return (write(2, "Please close the single qoute!\n", 32), 101);
	}
	return (0);
}

void	qoute_trim(t_node *tokens)
{
	t_node	*head;

	head = tokens;
	while (head)
	{
		if (head->state == IN_DOUBLEQ)
		{
			head->str = ft_strtrim(head->str, "\"");
		}
		else if (head->state == IN_SINGLEQ)
		{
			head->str = ft_strtrim(head->str, "\'");
		}
		head = head->next;
	}
}
