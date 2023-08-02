/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/02 12:55:35 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_parser_list	make_node_biglist(t_node *tokens, t_parser_list **p_list, t_parser_list *last)
// {
// 	if (tokens->type == REDIRECT_IN)
// 	{
// 		printf("going into rd_managment_in function\n");
// 		tokens = rd_managment_in(tokens, p_list);
// 		printf("going out of rd_managment_in function\n");
// 		last = ft_lastlist_lparser(*p_list);
// 		printf("HI 4\n");
// 		if (last->fd_in == -1)
// 			break;
// 		printf("hi 6\n");
// 	}
// 	else if (tokens->type == REDIRECT_OUT)
// 	{
// 		printf("going into rd_managment_out function\n");
// 		tokens = rd_managment_out(tokens, p_list);
// 		printf("going out of rd_managment_out function\n");
// 		last = ft_lastlist_lparser(*p_list);
// 		printf("HI out 4\n");
// 		if (last->fd_out == -1)
// 			break;
// 		printf("hi out 6\n");
// 	}
// 	else
// 	{
// 		n_list = make_node_parsertokens;
// 		printf("the token for parser list = %s\n", tokens->str);
// 		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
// 		last = ft_lastlist_lparser(*p_list);
// 		if (tokens->next != NULL)
// 			tokens = tokens->next;
// 	}
// }

void	make_parser(t_node **tokens, t_parser_list **p_list)
{
	t_parser_list	*last;
	t_parser_node	*n_list;
	t_node			*head;
	char			*line;

	n_list = NULL;
	last = NULL;
	line = 0;
	syntax_error(*tokens);
	printf("first token = %s\n", (*tokens)->str);
	head = *tokens;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL && (*tokens) == head)
		{
			if ((*tokens)->type == REDIRECT_IN)
			{
				printf("going into rd_managment_in function\n");
				*tokens = rd_managment_in(*tokens, p_list);
				printf("going out of rd_managment_in function\n");
				last = ft_lastlist_lparser(*p_list);
				printf("HI 4\n");
				if (last->fd_in == -1)
					break ;
				printf("hi 6\n");
			}
			else if ((*tokens)->type == REDIRECT_OUT)
			{
				printf("going into rd_managment_out function\n");
				*tokens = rd_managment_out(*tokens, p_list);
				printf("going out of rd_managment_out function\n");
				last = ft_lastlist_lparser(*p_list);
				printf("HI out 4\n");
				if (last->fd_out == -1)
					break ;
				printf("hi out 6\n");
			}
			else
			{
				n_list = make_node_parser(*tokens);
				printf("the token for parser list = %s\n", (*tokens)->str);
				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
				last = ft_lastlist_lparser(*p_list);
				if ((*tokens)->next != NULL)
					(*tokens) = (*tokens)->next;
			}
		}
		else
		{
			if ((head)->next == NULL && ft_sizelist(head) == 1)
			{
				n_list = make_node_parser(head);
				printf("if only one --> the token for parser list = %s\n", head->str);
				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
				last = ft_lastlist_lparser(*p_list);
				break ;
			}
			else
				break ;
		}
		if (*tokens == NULL)
			printf("I am NULL!\n");
		while((*tokens)->type != PIPE && (*tokens) != NULL)
		{
			printf("5 after the break str = %s and type = %d\n", (*tokens)->str, (*tokens)->type);
			while ((*tokens)->type == SPACE && (*tokens)->next != NULL)
			{
				(*tokens) = (*tokens)->next;
			}
			while ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			{
				printf("got ya = %s\n", (*tokens)->str);
				printf("this should be the rest of the list = ");
				print_list(*tokens);
				*tokens = rd_managment(*tokens, p_list);
				printf("we are here after rd managment = %s\n", (*tokens)->str);
				if ((*tokens)->type == PIPE || (*tokens)->next == NULL || last->fd_in == -1 || last->fd_out == -1)
					break;
				printf("I got out of the rd while\n");
			}
			if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && (last->rd_out == true || last->rd_in == true || last->rd_out_append == true || last->rd_in_heredoc == true))) //|| ((*tokens)->next == NULL && last->rd_in == true))
				break;
			if (last->fd_in == -1 || last->fd_out == -1)
				break;
			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			else
				break;
		}
		if (last->fd_in == -1 || last->fd_out == -1)
			break;
		if (last->rd_in_heredoc == true)
		{
			printf("I am getting here in heredoc and this is delimeter = .%s.\n", last->delimiter);
			while(1)
			{
				line = get_next_line(1);
				//printf("line= %s\n", line);
				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) != 0)
				{
					//printf("got here\n");
					write(last->fd_in, line, ft_strlen(line));
					free(line);
				}
				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) == 0)
					break;
			}
			close(last->fd_in);
			last->fd_in = open("here_doc", O_RDONLY);
		}
		while (((*tokens)->type == PIPE || (*tokens)->type == SPACE) && (*tokens) != NULL)
		{
			(*tokens) = (*tokens)->next;
			head = (*tokens);
		}
		if (*tokens == NULL)
			break;
	}
	printf("I got here\n");
	print_list_lparser(p_list);
	printf("its finished\n");
}


//fd leaks

//check syntax error at first

// I should take care of redirection in!

//echo < file2 is not working properly