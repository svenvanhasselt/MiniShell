/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 17:07:29 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 17:09:59 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup2_stdin_stdout(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		error_exit("operation failure", errno);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		error_exit("operation failure", errno);
}

int	builtins_redirect(t_exec **data, t_pl *parser, char ***env)
{
	int	*status;

	status = &(*data)->exit_status;
	if ((*data)->num_commands == 1)
	{
		(*data)->fdin_old = dup(STDIN_FILENO);
		(*data)->fdout_old = dup(STDOUT_FILENO);
		(*data)->fdin = redirect(parser, status, STDIN_FILENO, true);
		(*data)->fdout = redirect(parser, status, STDOUT_FILENO, false);
		if ((*data)->fdin < 0 || (*data)->fdout < 0)
			return (*status);
		dup2_stdin_stdout((*data)->fdin, (*data)->fdout);
		if (check_builtins(parser->cmd_table, env, \
		status, (*data)->prev_status))
		{
			dup2_stdin_stdout((*data)->fdin_old, (*data)->fdout_old);
			*status = free_data(*data, parser);
			return (*status);
		}
		dup2_stdin_stdout((*data)->fdin_old, (*data)->fdout_old);
	}
	return (-1);
}

int	check_builtins(char **cmd_table, char ***env, int *status, int prev_status)
{
	int	i;

	i = -1;
	if (!cmd_table[0])
		return (-1);
	while (cmd_table[0][++i])
		cmd_table[0][i] = ft_tolower(cmd_table[0][i]);
	if (strncmp(cmd_table[0], "cd", ft_strlen(cmd_table[0])) == 0)
		*status = cd_builtin(cmd_table, env);
	else if (strncmp(cmd_table[0], "echo", ft_strlen(cmd_table[0])) == 0)
		*status = echo_builtin(cmd_table);
	else if (strncmp(cmd_table[0], "env", ft_strlen(cmd_table[0])) == 0)
		*status = env_builtin((*env));
	else if (strncmp(cmd_table[0], "exit", ft_strlen(cmd_table[0])) == 0)
		*status = exit_builtin(cmd_table, prev_status);
	else if (strncmp(cmd_table[0], "export", ft_strlen(cmd_table[0])) == 0)
		*status = export_builtin(cmd_table, env);
	else if (strncmp(cmd_table[0], "pwd", ft_strlen(cmd_table[0])) == 0)
		*status = pwd_builtin();
	else if (strncmp(cmd_table[0], "unset", ft_strlen(cmd_table[0])) == 0)
		*status = unset_builtin(cmd_table[1], env);
	else
		return (0);
	return (1);
}

