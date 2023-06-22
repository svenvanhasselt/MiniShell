/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/22 14:29:42 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include "libft.h"

typedef struct s_funcstruc
{
	char	*name;
	void	(*func)(void*);
}	t_func;

typedef struct exec_struc
{
	int		infile;
	int		outfile;
	int		fdin;
	int		fdout;
	int		num_commands;
	int		**pipe_fd;
	int		*fork_pid;
	t_func	*builtin_func[7];
	char	*test_cmd[3][4];
}	t_exec;

void	execution(void);
void	close_pipes_files(t_exec *data);
void	waitpid_forks(t_exec *data);
void	create_pipes(t_exec *data);
// void	builtin_func(t_exec *data);
int		check_array_size(char **array);

/* Built-ins */
int		echo(char **cmd_table);
int		cd(char **cmd_table);

#endif