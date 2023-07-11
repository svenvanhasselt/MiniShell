/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/11 16:08:00 by svan-has      ########   odam.nl         */
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

enum e_minishell_errors {
	ERR_NO_CMD			= -1,
	ERR_EXPORT_INVALID	= -2,
	ERR_CD_FILE_UNAIV	= -3,
	ERR_CD_NO_HOME		= -4,
};

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
	int		exit_status;
	int		**pipe_fd;
	int		*fork_pid;
	t_func	*builtin_func[7];
	char	*test_cmd[3][4];
	char	**env;
}	t_exec;

/*	Main execution functions */
int		execution(void);
void	close_pipes_files(t_exec *data);
void	waitpid_forks(t_exec *data);
void	create_pipes(t_exec *data, int num_commands);
int		error_exit(char *message, int error_no);
int		error_seterrno(char *message, char *message2, int error_no);

/*	Built-ins */
int		echo_builtin(char **cmd_table);
int		cd_builtin(char **cmd_table, char ***env);
int		pwd_builtin(void);
int		env_builtin(char **env);
int		unset_builtin(char *variable, char ***env);
int		export_builtin(char **cmd_table, char ***env);
int		exit_builtin(int status);

/*	Tools */
char	**copy_environment_list(char **env);
int		array_size(char **array);
void	*null_check(void *check);
int		find_env_var(char *variable, char **env);
int		find_value(char *string);
int		add_variable(char *string, char ***env);

#endif