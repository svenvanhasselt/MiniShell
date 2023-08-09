/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_comb.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 17:01:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/09 19:42:39 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	combine_tokens(t_node **tokens)
{
	t_node	*head;
	t_node	*temp;

	head = *tokens;
	temp = NULL;
	while (head)
	{
		if (((head->state == IN_SINGLEQ || head->state == IN_DOUBLEQ) && ((head->next && head->next->type == WORD))) || \
		((head->state == NORMAL && head->type == WORD) && (head->next && (head->next->state == IN_DOUBLEQ || head->next->state == IN_SINGLEQ))))
		{
			temp = head->next;
			head->str = ft_strjoin(head->str, head->next->str);
			head->len = ft_strlen(head->str);
			head->state = IN_SINGLEQ;
			if (temp != NULL)
			{
				if (temp->next == NULL)
					head->next = NULL;
				else
				{
					head->next = head->next->next;
					temp->next = NULL;
				}
				free(temp->str);
				free(temp);
			}
			else if (temp == NULL)
			{
				free(temp->str);
				free(temp);
				head->next = NULL;
				break ;
			}
		}
		else
			head = head->next;
	}
}

//  void	combine_tokens(t_node **tokens)
// {
// 	t_node	*head;
// 	t_node	*temp;

// 	head = *tokens;
// 	temp = NULL;
// 	while (head)
// 	{
// 		printf("We are in the combine tokens function:\n");
// 		if (((head->state == IN_SINGLEQ || head->state == IN_DOUBLEQ) && ((head->next && head->next->type == WORD))) ||\
// 		((head->state == NORMAL && head->type == WORD) && (head->next && (head->next->state == IN_DOUBLEQ || head->next->state == IN_SINGLEQ))))
// 		{
// 			printf("found the single qoute or double\n");
// 			printf("this is the head str before join = .%s.\n", head->str);
// 			temp = head->next;
// 			head->str = ft_strjoin(head->str, head->next->str);
// 			printf("head->str after strjoin = .%s.\n", head->str);
// 			head->len = ft_strlen(head->str);
// 			head->state = IN_SINGLEQ;
// 			if (temp != NULL)
// 			{
// 				printf("temp is not NULL\n");
// 				if (temp->next == NULL)
// 				{
// 					printf("in if\n");
// 					head->next = NULL;
// 					free(temp->str);
// 					free(temp);
// 					printf("this is the head->str in if = .%s.\n", head->str);
// 				}
// 				else
// 				{
// 					printf("in else\n");
// 					head->next = head->next->next;
// 					// head = head->next;
// 					temp->next = NULL;
// 					free(temp->str);
// 					free(temp);
// 					printf("this is the head->str in else = .%s.\n", head->str);
// 				}
// 			}
// 			else if (temp == NULL)
// 			{
// 				printf("temp is NULL!\n");
// 				// head = head->next;
// 				free(temp->str);
// 				free(temp);
// 				head->next = NULL;
// 				break;
// 			}
// 			printf("1 this is the str now before going further in if= .%s.\n", head->str);
// 		}
// 		// else if ((head->state == NORMAL && head->type == WORD) && (head->next && (head->next->state == IN_DOUBLEQ || head->next->state == IN_SINGLEQ)))
// 		// {
// 		// 	printf("found the single qoute or double\n");
// 		// 	printf("this is the head str before join = .%s.\n", head->str);
// 		// 	temp = head->next;
// 		// 	head->str = ft_strjoin(head->str, head->next->str);
// 		// 	printf("head->str after strjoin = .%s.\n", head->str);
// 		// 	head->len = ft_strlen(head->str);
// 		// 	head->state = IN_SINGLEQ;
// 		// 	if (temp != NULL)
// 		// 	{
// 		// 		printf("temp is not NULL\n");
// 		// 		if (temp->next == NULL)
// 		// 		{
// 		// 			printf("in if\n");
// 		// 			head->next = NULL;
// 		// 			free(temp->str);
// 		// 			free(temp);
// 		// 			printf("this is the head->str in if = .%s.\n", head->str);
// 		// 		}
// 		// 		else
// 		// 		{
// 		// 			printf("in else\n");
// 		// 			head->next = head->next->next;
// 		// 			// head = head->next;
// 		// 			temp->next = NULL;
// 		// 			free(temp->str);
// 		// 			free(temp);
// 		// 			printf("this is the head->str in else = .%s.\n", head->str);
// 		// 		}
// 		// 	}
// 		// 	else if (temp == NULL)
// 		// 	{
// 		// 		printf("temp is NULL!\n");
// 		// 		// head = head->next;
// 		// 		free(temp->str);
// 		// 		free(temp);
// 		// 		head->next = NULL;
// 		// 		break;
// 		// 	}
// 		// 	printf("1 this is the str now before going further in if= .%s.\n", head->str);
// 		// }
// 		else
// 		{
// 			printf("2 this is the str now before going further in else = .%s. state = %d and type = %d\n", head->str, head->state, head->type);
// 			head = head->next;
// 			//printf("2 this is the str now after going further in else = .%s. state = %d and type = %d\n", head->str, head->state, head->type);
// 		}
// 	}
// 	printf("this is the tokens result after the combine and trim->");
// 	print_list(*tokens);
// 	printf("we got out from the printing\n");
// 	printf("getting out of the while loop\n");
// }