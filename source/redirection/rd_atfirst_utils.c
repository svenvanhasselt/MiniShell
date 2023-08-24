/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_atfirst_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 17:57:44 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/23 17:37:12 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rd_atfirst_out_utils(t_node *head, t_pl *node)
{
	node->rd_out = true;
	free(node->file_out);
	node->file_out = ft_strdup(head->str);
	close(node->fd_out);
	if (node->rd_out_append == true)
		node->fd_out = open(head->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->rd_out_append == false)
		node->fd_out = open(head->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
		node->errno_in = errno;
}

void	rd_atfirst_in_utils(t_node *head, t_pl *node)
{
	char	*line;

	line = NULL;
	node->rd_in = true;
	close(node->fd_in);
	if (node->rd_in_heredoc == false)
	{
		free(node->file_in);
		node->file_in = ft_strdup(head->str);
	}
	if (node->rd_in_heredoc == true)
	{
		free(node->del_without_nl);
		node->del_without_nl = ft_strdup(head->str);
		printf("node->del_without_nl = %s\n", node->del_without_nl);
		free(node->delimiter);
		node->delimiter = ft_strjoin(head->str, "\n");
		free(node->file_in);
		node->file_in = ft_strdup("here_doc");
		rd_heredoc(node);
	}
	else if (node->rd_in_heredoc == false)
		node->fd_in = open(head->str, O_RDONLY);
	if (node->fd_in == -1)
		node->errno_in = errno;
}

t_node	*rd_makelist_utils(t_node *tokens, t_node *first_command, t_pl **p_list)
{
	char	*after_rd;
	t_pn	*n_list;

	after_rd = NULL;
	n_list = NULL;
	if (tokens->type == WORD)
	{
		after_rd = tokens->str;
		if (tokens->next != NULL)
			tokens = tokens->next;
		if (tokens->next != NULL)
			tokens = tokens->next;
	}
	if (tokens->type == WORD && \
	ft_strncmp(tokens->str, after_rd, ft_strlen(after_rd)) != 0)
	{
		first_command = tokens;
		n_list = make_node_parser(tokens);
		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
		tokens = tokens->next;
	}
	return (tokens);
}

// t_node	*rd_makelist_utils(t_node *tokens, t_node *first_command, t_pl **p_list)
// {
// 	char	*after_rd;
// 	t_pn	*n_list;

// 	after_rd = NULL;
// 	n_list = NULL;
// 	after_rd = tokens->str;
// 	if (tokens->next != NULL)
// 			tokens = tokens->next;
// 	while (tokens && tokens->type == SPC)
// 		tokens = tokens->next;
// 	while (tokens && (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT))
// 	{
// 		while(tokens && tokens->type != PIPE && tokens->type != WORD)
// 			tokens = tokens->next;
// 		if(tokens && tokens->type == WORD)
// 		{
// 			after_rd = tokens->str;
// 			printf("this is the after_rd = %s\n", after_rd);
// 			if (tokens->next != NULL)
// 				tokens = tokens->next;
// 		}
// 		if (tokens && tokens->type == PIPE)
// 			return (NULL);
// 	}
// 	while (tokens && tokens->type == SPC)
// 		tokens = tokens->next;
// 	printf("in utils tokens->str = %s\n", tokens->str);
// 	if (tokens->type == WORD && \
// 	ft_strncmp(tokens->str, after_rd, ft_strlen(after_rd)) != 0)
// 	{
// 		first_command = tokens;
// 		printf("here\n");
// 		printf("in makelist utils first command = %s\n", first_command->str);
// 		n_list = make_node_parser(tokens);
// 		ft_add_back_list_lparser(p_list, make_node_lparser(n_list));
// 		// tokens = tokens->next;
// 	}
// 	//printf("in utils first command= %s\n", first_command->str);
// 	return (first_command);
// }
