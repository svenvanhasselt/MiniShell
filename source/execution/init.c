/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sven <sven@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:45:46 by svan-has          #+#    #+#             */
/*   Updated: 2023/08/07 10:21:49 by sven             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*prepare(t_parser_list *parser, char ***env)
{
	int			i;
	t_exec		*data;

	data = null_check(malloc (1 * sizeof(t_exec)));
	data->num_commands = ft_sizelist_lparser(parser);
	data->fork_pid = null_check(malloc(data->num_commands * sizeof(int)));
	data->pipe_fd = null_check(malloc((data->num_commands - 1) \
	* sizeof(int *)));
	i = -1;
	while (++i < data->num_commands - 1)
		data->pipe_fd[i] = null_check(malloc (2 * sizeof(int)));
	data->env = (*env);
	create_cmd_table(parser);
	return (data);
}
