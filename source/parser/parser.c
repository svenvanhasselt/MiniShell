/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/14 14:20:59 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parser_utils(t_node *tokens, t_pl **p_list)
{
	t_pl	*last;

	last = ft_lastlist_lparser(*p_list);
	while (tokens != NULL && tokens->type != PIPE)
	{
		while (tokens->type == SPACE && tokens->next != NULL)
			tokens = tokens->next;
		while (tokens->type == REDIRECT_OUT || tokens->type == REDIRECT_IN)
		{
			tokens = rd_managment(tokens, p_list);
			if (tokens->type == PIPE || tokens->next == NULL \
			|| last->fd_in == -1 || last->fd_out == -1)
				break ;
		}
		if (tokens->type == PIPE || (tokens->next == NULL && \
		(last->rd_out == true || last->rd_in == true)))
			break ;
		if (last->fd_in == -1 || last->fd_out == -1)
			break ;
		ft_add_back_list_parser(&(last->lst), make_node_parser(tokens));
		tokens = tokens->next;
	}
	return (tokens);
}

t_node	*first_list_pl(t_node *tokens, t_pl **p_list)
{
	t_pn	*n_list;

	n_list = NULL;
	if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT)
		tokens = rd_atfirst_managment(tokens, p_list);
	else
	{
		printf("this is the str = %s\n", tokens->str);
		n_list = make_node_parser(tokens);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		if (tokens->next != NULL)
			tokens = tokens->next;
	}
	return (tokens);
}

t_node	*special_last(t_node *tokens, t_node *head, t_pl **p_list)
{
	t_pn	*n_list;
	t_pl	*last;

	if ((head)->next == NULL && ft_sizelist(head) == 1)
	{
		n_list = make_node_parser(head);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		return (NULL);
	}
	last = ft_lastlist_lparser(*p_list);
	n_list = last->lst;
	if (tokens->next == NULL && ((last->rd_in_heredoc == true && \
	ft_strncmp(tokens->str, last->del_without_nl, \
	ft_strlen(last->del_without_nl)) != 0) || \
	last->rd_out == true || last->rd_in == true))
	{
		ft_add_back_list_parser(&n_list, make_node_parser(tokens));
		tokens = tokens->next;
	}
	else
	{
		printf("it is not rare!!!!!\n\n");
		return (NULL);
	}
	return (tokens);
}

void	make_parser(t_node **tokens, t_pl **p_list)
{
	t_pl	*last;
	t_node	*head;

	last = NULL;
	qoute_trim(*tokens);
	combine_tokens(*tokens);
	head = *tokens;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->next != NULL && (*tokens) == head)
			*tokens = first_list_pl(*tokens, p_list);
		else
			*tokens = special_last(*tokens, head, p_list);
		last = ft_lastlist_lparser(*p_list);
		if (last->fd_in == -1 || last->fd_out == -1)
			break ;
		*tokens = parser_utils(*tokens, p_list);
		while ((*tokens) != NULL && ((*tokens)->type == PIPE \
		|| (*tokens)->type == SPACE))
		{
			(*tokens) = (*tokens)->next;
			head = (*tokens);
		}
	}
}

// I should check where to put the heredoc!

//fd leaks

//check syntax error at first

// I should take care of redirection in!

//echo < file2 is not working properly
