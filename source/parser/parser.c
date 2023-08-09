/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/09 16:16:19 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_parser(t_node **tokens, t_pl **p_list)
{
	t_pl	*last;
	t_pn	*n_list;
	t_node			*head;
	char			*line;

	n_list = NULL;
	last = NULL;
	line = 0;
	qoute_trim(*tokens);
	combine_tokens(tokens);
	head = *tokens;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL && (*tokens) == head)
		{
			if ((*tokens)->type == REDIRECT_IN || (*tokens)->type == REDIRECT_OUT)
			{
				*tokens = rd_atfirst_managment(*tokens, p_list);
				last = ft_lastlist_lparser(*p_list);
				if (last->fd_in == -1 || last->fd_out == -1)
					break ;
			}
			else
			{
				n_list = make_node_parser(*tokens);
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
				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
				last = ft_lastlist_lparser(*p_list);
				break ;
			}
			if ((*tokens)->next == NULL && ((last->rd_in_heredoc == true && ft_strncmp((*tokens)->str, last->del_without_nl, ft_strlen(last->del_without_nl)) != 0)|| last->fd_out == true || last->fd_in == true))
			{
				ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
				(*tokens) = (*tokens)->next;
				break ;
			}
			else
				break ;
		}
		while ((*tokens) != NULL && (*tokens)->type != PIPE)
		{
			while ((*tokens)->type == SPACE && (*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			while ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			{
				*tokens = rd_managment(*tokens, p_list);
				if ((*tokens)->type == PIPE || (*tokens)->next == NULL || last->fd_in == -1 || last->fd_out == -1)
					break;
			}
			// if ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
			// {
			// 	*(tokens) = rd_managment(*tokens, p_list);
			// 	if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && (last->rd_out == true || last->rd_in == true || last->rd_out_append == true || last->rd_in_heredoc == true)))
			// 	{
			// 		printf("here is the tokens str if it is the last = %s\n", (*tokens)->str);
			// 		break;
			// 	}
			// 	if (last->fd_in == -1 || last->fd_out == -1)
			// 		break ;
			// }
			printf("this is the last = %s\n", last->lst->str);
			//I can not find why I have puted this here!
			if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && (last->rd_out == true || last->rd_in == true || last->rd_out_append == true || last->rd_in_heredoc == true)))
			{
				printf("here is the tokens str if it is the last = %s\n", (*tokens)->str);
				break;
			}
			if (last->fd_in == -1 || last->fd_out == -1)
				break;
			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
			if ((*tokens)->next != NULL)
				(*tokens) = (*tokens)->next;
			else
				break;
		}
		if (last->rd_in_heredoc == true)
		{
			while(1)
			{
				line = get_next_line(1);
				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) != 0)
				{
					write(last->fd_in, line, ft_strlen(line));
					free(line);
				}
				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) == 0)
					break;
			}
			close(last->fd_in);
			last->fd_in = open("here_doc", O_RDONLY);
		}
		while ( (*tokens) != NULL && ((*tokens)->type == PIPE || (*tokens)->type == SPACE))
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

// I should check where to put the heredoc!

//fd leaks

//check syntax error at first

// I should take care of redirection in!

//echo < file2 is not working properly


// void	make_parser(t_node **tokens, t_pl **p_list)
// {
// 	t_pl	*last;
// 	t_parser_node	*n_list;
// 	t_node			*head;
// 	char			*line;

// 	n_list = NULL;
// 	last = NULL;
// 	line = 0;
// 	//syntax_error(*tokens);
// 	qoute_trim(*tokens);
// 	combine_tokens(tokens);
// 	// printf("out of combine tokens\n");
// 	// printf("first token = %s\n", (*tokens)->str);
// 	head = *tokens;
// 	// printf("hi i am in Parser!\n");
// 	while ((*tokens) != NULL)
// 	{
// 		// printf("tokens = %s\n", (*tokens)->str);
// 		if ((*tokens)->next != NULL && (*tokens) == head)
// 		{
// 			// printf("the first if \n");
// 			if ((*tokens)->type == REDIRECT_IN)
// 			{
// 				// printf("going into rd_managment_in function\n");
// 				*tokens = rd_managment_in(*tokens, p_list);
// 				// printf("going out of rd_managment_in function\n");
// 				last = ft_lastlist_lparser(*p_list);
// 				// printf("HI 4\n");
// 				if (last->fd_in == -1)
// 					break ;
// 				// printf("hi 6\n");
// 			}
// 			else if ((*tokens)->type == REDIRECT_OUT)
// 			{
// 				// printf("going into rd_managment_out function\n");
// 				*tokens = rd_managment_out(*tokens, p_list);
// 				// printf("going out of rd_managment_out function\n");
// 				last = ft_lastlist_lparser(*p_list);
// 				// printf("HI out 4\n");
// 				if (last->fd_out == -1)
// 					break ;
// 				// printf("hi out 6\n");
// 			}
// 			else
// 			{
// 				n_list = make_node_parser(*tokens);
// 				// printf("the token for parser list = %s\n", (*tokens)->str);
// 				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
// 				last = ft_lastlist_lparser(*p_list);
// 				if ((*tokens)->next != NULL)
// 					(*tokens) = (*tokens)->next;
// 			}
// 		}
// 		else
// 		{
// 			// printf("you are right we got here! and this is the size list = %d\n", ft_sizelist(head));
// 			if ((head)->next == NULL && ft_sizelist(head) == 1)
// 			{
// 				n_list = make_node_parser(head);
// 				// printf("if only one --> the token for parser list = %s\n", head->str);
// 				ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
// 				last = ft_lastlist_lparser(*p_list);
// 				break ;
// 			}
// 			if ((*tokens)->next == NULL && (last->rd_in_heredoc == true || last->fd_out == true || last->fd_in == true))
// 			{
// 				// printf("in the new if and this is the tokens = %s\n", (*tokens)->str);
// 				// printf("if we are the last one--> the token for parser list = %s\n", (*tokens)->str);
// 				ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
// 				(*tokens) = (*tokens)->next;
// 				// printf("print the list in the new if: \n");
// 				// print_list_lparser(p_list);
// 				break ;
// 			}
// 			else
// 				break ;
// 		}
// 		// printf("I got here too!\n");
// 		if (last->rd_in_heredoc == true)
// 		{
// 			// printf("I am getting here in heredoc and this is delimeter = .%s.\n", last->delimiter);
// 			while(1)
// 			{
// 				line = get_next_line(1);
// 				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) != 0)
// 				{
// 					write(last->fd_in, line, ft_strlen(line));
// 					free(line);
// 				}
// 				if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) == 0)
// 					break;
// 			}
// 			close(last->fd_in);
// 			last->fd_in = open("here_doc", O_RDONLY);
// 		}
// 		// printf("this is the tokens now = %s\n", (*tokens)->str);
// 		while ((*tokens) != NULL && (*tokens)->type != PIPE)
// 		{
// 			// printf("5 after the break str = %s and type = %d\n", (*tokens)->str, (*tokens)->type);
// 			while ((*tokens)->type == SPACE && (*tokens)->next != NULL)
// 			{
// 				(*tokens) = (*tokens)->next;
// 			}
// 			while ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == REDIRECT_IN)
// 			{
// 				// printf("got ya = %s\n", (*tokens)->str);
// 				// printf("this should be the rest of the list = ");
// 				// print_list(*tokens);
// 				*tokens = rd_managment(*tokens, p_list);
// 				// printf("we are here after rd managment = %s\n", (*tokens)->str);
// 				if ((*tokens)->type == PIPE || (*tokens)->next == NULL || last->fd_in == -1 || last->fd_out == -1)
// 					break;
// 				// printf("I got out of the rd while\n");
// 			}
// 			if ((*tokens)->type == PIPE || ((*tokens)->next == NULL && (last->rd_out == true || last->rd_in == true || last->rd_out_append == true || last->rd_in_heredoc == true))) //|| ((*tokens)->next == NULL && last->rd_in == true))
// 				break;
// 			if (last->fd_in == -1 || last->fd_out == -1)
// 				break;
// 			ft_add_back_list_parser(&n_list, make_node_parser(*tokens));
// 			if ((*tokens)->next != NULL)
// 				(*tokens) = (*tokens)->next;
// 			else
// 				break;
// 		}
// 		// printf("I got here too!\n");
// 		// if (last->rd_in_heredoc == true)
// 		// {
// 		// 	// printf("I am getting here in heredoc and this is delimeter = .%s.\n", last->delimiter);
// 		// 	while(1)
// 		// 	{
// 		// 		line = get_next_line(1);
// 		// 		if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) != 0)
// 		// 		{
// 		// 			write(last->fd_in, line, ft_strlen(line));
// 		// 			free(line);
// 		// 		}
// 		// 		if (ft_strncmp(line, last->delimiter, ft_strlen(last->delimiter)) == 0)
// 		// 			break;
// 		// 	}
// 		// 	close(last->fd_in);
// 		// 	last->fd_in = open("here_doc", O_RDONLY);
// 		// }
// 		// printf("this is the tokens now = %s\n", (*tokens)->str);
// 		while ( (*tokens) != NULL && ((*tokens)->type == PIPE || (*tokens)->type == SPACE))
// 		{
// 			// printf("into the last while\n");
// 			(*tokens) = (*tokens)->next;
// 			head = (*tokens);
// 			// printf("this is the head now = %s\n", head->str);
// 		}
// 		if (*tokens == NULL)
// 			break;
// 		// printf("after the last while\n");
// 	}
// 	// printf("I got here\n");
// 	// print_list_lparser(p_list);
// 	// printf("its finished\n");
// }