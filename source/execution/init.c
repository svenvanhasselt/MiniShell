/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:45:46 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 17:11:50 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_cmd_table(t_pl *parser);

void	*prepare(t_pl **parser, char ***env)
{
	int			i;
	t_exec		*data;
	t_pl		*head;

	head = *parser;
	data = null_check(malloc (1 * sizeof(t_exec)));
	data->num_commands = ft_sizelist_lparser(*parser);
	data->fork_pid = null_check(malloc(data->num_commands * sizeof(int)));
	data->pipe_fd = null_check(malloc((data->num_commands - 1) \
	* sizeof(int *)));
	i = -1;
	while (++i < data->num_commands - 1)
		data->pipe_fd[i] = null_check(malloc (2 * sizeof(int)));
	data->env = (*env);
	create_cmd_table(head);
	return (data);
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
			if (head_lst->str)
				head->cmd_table[i] = ft_strdup(head_lst->str);
			else
				head->cmd_table[i] = NULL;
			head_lst = head_lst->next;
			i++;
		}
		head->cmd_table[i] = NULL;
		head = head->next;
	}
}
int free_data(t_exec *data, t_pl *parser)
{
	int	i;
	int	 exit_status;
	t_pl	*head;
	head = parser;
	exit_status = data->exit_status;
	i = 0;
	while (i < data->num_commands - 1)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
	free(data->fork_pid);
	free(data);
	return (exit_status);
}
