/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   qoute_trim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:58:19 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/02 18:00:02 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qoute_trim(t_node *tokens)
{
	t_node	*head;

	head = tokens;
	while(head)
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

// void	combine_tokens(t_node *tokens)
// {
// 	t_node	*head;
// 	t_node	*temp;

// 	head = tokens;
// 	temp = NULL;
// 	while(head->next != NULL)
// 	{
// 		printf("lets go\n");
// 		if (head->state == IN_DOUBLEQ)
// 		{
// 			printf("I got to the if double qoute\n");
// 			if (head->next != NULL && head->next->type == WORD)
// 			{
// 				temp = head->next;
// 				head->str = ft_strjoin(head->str, head->next->str);
// 				printf("this is the combined str = %s\n", head->str);
// 				head->len = ft_strlen(head->str);
// 				if (head->next != NULL && head->next->next != NULL)
// 					head->next = head->next->next;
// 				if (head->next == NULL)
// 					break;
// 				if (temp)
// 				{
// 					free(temp->str);
// 					free(temp);
// 				}
// 			}
// 		}
// 		if (head->state == IN_SINGLEQ)
// 		{
// 			if (head->next != NULL && head->next->type == WORD)
// 			{
// 				temp = head->next;
// 				head->str = ft_strjoin(head->str, head->next->str);
// 				head->len = ft_strlen(head->str);
// 				if (head->next != NULL && head->next->next != NULL)
// 					head->next = head->next->next;
// 				if (head->next == NULL)
// 					head->next = NULL;
// 				free(temp->str);
// 				free(temp);
// 			}
// 		}
// 		printf("this is the str now before going further = %s\n", head->str);
// 		if (head->next != NULL)
// 			head = head->next;
// 		// else
// 		// 	break;
// 		// if (head && head->next)
// 		// 	printf("this is the str after i got further = %s\n", head->str);
// 		printf("getting out\n");
// 	}
// }
 //I should test this code!