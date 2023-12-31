/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:45:46 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/12 14:43:00 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_cmd_table(t_pl *parser);

int	ft_sizelist_init(t_pl *lst)
{
	int		count;
	t_pl	*head;

	count = 0;
	if (!lst)
		return (0);
	head = lst;
	while (head != NULL)
	{
		if (head->lst->str != NULL && head->next != NULL)
			count++;
		head = head->next;
	}
	return (count);
}

void	*prepare(t_pl **parser, char ***env)
{
	int			i;
	t_exec		*data;
	t_pl		*head;

	head = *parser;
	data = null_check(malloc (1 * sizeof(t_exec)));
	if (head->lst->str == NULL && head->next == NULL)
		data->num_commands = 0;
	else
		data->num_commands = ft_sizelist_lparser(*parser);
	if (data->num_commands > 0)
	{
		data->fork_pid = null_check(malloc(data->num_commands * sizeof(int)));
		data->pipe_fd = null_check(malloc((data->num_commands - 1) \
		* sizeof(int *)));
	}
	i = -1;
	while (++i < data->num_commands - 1)
		data->pipe_fd[i] = null_check(malloc (2 * sizeof(int)));
	data->env = (*env);
	create_cmd_table(head);
	return (data);
}

int	create_new_table(t_pn **head_lst, t_pl **head, int i)
{
	if ((*head_lst)->str && !ft_strncmp((*head_lst)->str, "", \
	ft_strlen((*head_lst)->str)))
	{
		*head_lst = (*head_lst)->next;
		return (0);
	}
	if ((*head_lst)->str)
		(*head)->cmd_table[i] = ft_strdup((*head_lst)->str);
	else
		(*head)->cmd_table[i] = NULL;
	return (1);
}

void	create_cmd_table(t_pl *parser)
{
	int		i;
	int		size;
	t_pl	*head;
	t_pn	*head_lst;

	head = parser;
	while (head)
	{
		i = 0;
		head_lst = head->lst;
		size = ft_sizelist_parser(head_lst);
		head->cmd_table = null_check(malloc ((size + 1) * sizeof(char *)));
		while (head_lst)
		{
			if (!create_new_table(&head_lst, &head, i))
				continue ;
			head_lst = head_lst->next;
			i++;
		}
		head->cmd_table[i] = NULL;
		head = head->next;
	}
}

void	free_data(t_exec *data, t_pl *parser)
{
	int		i;
	t_pl	*head;

	head = parser;
	if (data->num_commands == 1)
	{
		close(data->fdin_old);
		close(data->fdout_old);
	}
	i = 0;
	while (i < data->num_commands - 1)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	if (data->num_commands > 0)
	{
		free(data->pipe_fd);
		free(data->fork_pid);
	}
	free(data);
}
