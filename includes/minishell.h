/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/17 18:28:00 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"

//********LEXER*************
enum e_token
{
	WORD = -1,
	SPACE = ' ',
	NEW_LINE = '\n',
	SINGLE_QOUTE = '\'',
	DOUBLE_QOUTE = '\"',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	ENV = '$',
};

enum e_situation
{
	NORMAL,
	IN_SINGLEQ,
	IN_DOUBLEQ,
};

typedef struct s_node
{
	char	*str;
	int		len;
	enum e_token type;
	enum e_situation state;
	struct s_node	*next;
	struct s_node	*prev;
}		t_node;

typedef struct s_lst
{
	t_node	*first;
	t_node	*last;
	int		list_size;
}	t_lst;

//******Parser********

enum e_node_type
{
	RD,
	CMD,
};

typedef struct s_parser_node
{
	// enum e_node_type n_type;
	struct s_parser_node	*nxt_node;
	struct s_parser_node	*prev_node;
	char			*str;
}				t_parser_node;

typedef struct s_parser_list
{
	t_parser_node	*lst;
	struct s_parser_list *next;
	bool			rd_in;
	int				fd_in;
	char			*file_in;
	int				errno_in;
	bool			rd_out;
	int				fd_out;
	char			*file_out;
	int				errno_out;
}				t_parser_list;

int		main();
char	*ft_readline(char *prompt);
void	check_line(char *line, t_node **lst);
t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state);
t_node	*ft_lastlist(t_node *lst);
void	ft_add_back_list(t_node **lst, t_node *new);
int		ft_sizelist(t_node *lst);
void	print_list(t_node *lst);
void	free_tokens(t_node **lst);
//--------Parser Node functions
t_parser_node	*make_node_parser(t_node *tokens);
t_parser_node	*ft_lastlist_parser(t_parser_node *lst);
void			ft_add_back_list_parser(t_parser_node **lst, t_parser_node *new);
int				ft_sizelist_parser(t_parser_node *lst);
void			print_list_parser(t_parser_node *lst);
void			free_list(t_parser_node *lst);
//-----Parser list functions
t_parser_list	*make_node_lparser(t_parser_node *small_list);
t_parser_list	*ft_lastlist_lparser(t_parser_list *lst);
void			ft_add_back_list_lparser(t_parser_list **lst, t_parser_list *new);
int				ft_sizelist_lparser(t_parser_list *lst);
void			print_list_lparser(t_parser_list **plist);
t_node			*rd_managment(t_node *tokens, t_parser_list **p_list);
void			free_llist(t_parser_list **p_list);
//-----Parser
void	make_parser(t_node **tokens, t_parser_list **p_list);
void	syntax_error(t_node *tokens);
// int		ft_checkline(char *s);
// int		count_words_msh(char *s);
// int		count_words(char const	*s, char c);
// char	**count_arrays_msh(char	*s, char **new);
// int		ft_free(char	**new, int words);

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