/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 12:11:10 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/08 10:44:55 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*first_list_pl(t_node *tokens, t_pl **p_list, char ***env)
{
	t_pn	*n_list;

	n_list = NULL;
	if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT)
		tokens = rd_atfirst_managment(tokens, p_list, env);
	else
	{
		n_list = make_node_parser(tokens);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		tokens = tokens->next;
	}
	return (tokens);
}

t_node	*special_last(t_node *tokens, t_node *head, t_pl **p_list)
{
	t_pn	*n_list;
	t_pl	*last;

	if (tokens->next == NULL && (*p_list) && \
	(*p_list)->lst == NULL && ft_sizelist_lparser(*p_list) == 1)
		return (NULL);
	if ((head)->next == NULL && ft_sizelist(head) == 1)
	{
		n_list = make_node_parser(head);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		return (NULL);
	}
	last = ft_lastlist_lparser(*p_list);
	n_list = last->lst;
	if (!(last->rd_in == true && last->rd_out == true) && ((last->rd_in_heredoc \
	== true && ft_strncmp(tokens->str, last->del_without_nl, \
	ft_strlen(last->del_without_nl)) != 0) || (last->rd_out == true && \
	ft_strncmp(tokens->str, last->file_out, \
	ft_strlen(last->file_out)) != 0) || (last->rd_in == true && \
	ft_strncmp(tokens->str, last->file_in, \
	ft_strlen(last->file_in)) != 0)))
		ft_add_back_list_parser(&n_list, make_node_parser(tokens));
	return (NULL);
}

t_node	*first_last(t_node *tokens, t_node *head, t_pl **p_list, char ***env)
{
	if (tokens && tokens->next != NULL && tokens == head)
		tokens = first_list_pl(tokens, p_list, env);
	else if (tokens && tokens->next == NULL)
		tokens = special_last(tokens, head, p_list);
	return (tokens);
}

t_node	*parser_utils(t_node *tokens, t_pl **p_list, char ***env)
{
	t_pl	*last;

	last = ft_lastlist_lparser(*p_list);
	while (last && tokens != NULL && tokens->type != PIPE)
	{
		while (tokens->type == SPC && tokens->next != NULL)
			(tokens) = (tokens)->next;
		while (tokens && (tokens->type == REDIRECT_OUT || \
		tokens->type == REDIRECT_IN))
		{
			tokens = rd_managment(tokens, p_list, env);
			if (last->fd_in == -1 || last->fd_out == -1 || \
			tokens->type == PIPE || tokens->next == NULL)
				break ;
		}
		if ((tokens && tokens->type == PIPE) || \
		(tokens && tokens->next == NULL && \
		(last->rd_out == true || last->rd_in == true)))
			break ;
		if (last->fd_in == -1 || last->fd_out == -1)
			break ;
		ft_add_back_list_parser(&(last->lst), make_node_parser(tokens));
		tokens = tokens->next;
	}
	return (tokens);
}

t_node	*make_parser(t_node **tokens, t_pl **p_list, char ***env)
{
	t_pl	*last;
	t_node	*head;
	t_node	*first_token;

	last = NULL;
	first_token = prepare_tokens(tokens);
	head = *tokens;
	while ((*tokens) != NULL)
	{
		*tokens = first_last(*tokens, head, p_list, env);
		if (*tokens)
		{
			last = ft_lastlist_lparser(*p_list);
			if (last && (last->fd_in == -1 || last->fd_out == -1))
				break ;
			*tokens = parser_utils(*tokens, p_list, env);
			while ((*tokens) != NULL && ((*tokens)->type == PIPE \
			|| (*tokens)->type == SPC))
			{
				(*tokens) = (*tokens)->next;
				head = (*tokens);
			}
		}
	}
	return (first_token);
}

// if ((*tokens)->next != NULL && (*tokens) == head)
// 	*tokens = first_list_pl(*tokens, p_list, env);
// else if ((*tokens) && (*tokens)->next == NULL)
// 	*tokens = special_last(*tokens, head, p_list);

// I should check where to put the heredoc!

//fd leaks

//check syntax error at first

// I should take care of redirection in!

//echo < file2 is not working properly
