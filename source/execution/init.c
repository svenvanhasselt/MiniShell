/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:45:46 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/21 18:16:17 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*prepare(t_parser_list *parser, char **env)
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
	data->env = env;
	create_cmd_table(parser);
	return (data);
}