/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/12 11:03:54 by psadeghi      ########   odam.nl         */
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

/* STRUCT'S */

/* LEXER STRUCT'S */
enum e_token
{
	WORD = -1,
	SPC = ' ',
	NEW_LINE = '\n',
	SINGLE_QOUTE = '\'',
	DOUBLE_QOUTE = '\"',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	ENV = '$',
};

enum e_state
{
	NORMAL,
	IN_SINGLEQ,
	IN_DOUBLEQ,
	EXP,
};

typedef struct s_node
{
	char			*str;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_node	*next;
}		t_node;

/* PARSER STRUCT'S */
enum e_node_type
{
	RD,
	CMD,
};

typedef struct s_pn
{
	struct s_pn	*next;
	char		*str;
}				t_pn;

typedef struct s_pl
{
	t_pn		*lst;
	struct s_pl	*next;
	char		**cmd_table;
	bool		rd_in;
	int			fd_in;
	char		*file_in;
	int			errno_in;
	bool		rd_out;
	int			fd_out;
	char		*file_out;
	int			errno_out;
	bool		rd_out_append;
	bool		rd_in_heredoc;
	char		*delimiter;
	char		*del_without_nl;
	int			exit_code;
}				t_pl;

typedef struct s_main
{
	char	*line;
	t_node	*lst;
	char	*new;
	t_pl	*p_list;
	char	**env;
	int		exit_status;
}	t_mdata;

enum e_minishell_errors {
	ERR_NO_CMD			= -1,
	ERR_EXPORT_INVALID	= -2,
	ERR_CD_FILE_UNAIV	= -3,
	ERR_CD_NO_HOME		= -4,
	ERR_CD_NOT_DIR		= -5,
	ERR_EXIT_ARG		= -6,
	ERR_EXIT_NUM		= -7,
};

typedef struct s_exec_struc
{
	int		fdin;
	int		fdout;
	int		fdin_old;
	int		fdout_old;
	bool	fdin_pipe;
	bool	fdout_pipe;
	int		num_commands;
	int		*exit_status;
	int		**pipe_fd;
	int		*fork_pid;
	char	**cmd_table;
	char	**env;
	t_pl	*parser_node;
}	t_exec;

/* LEXER */
void	make_tokens(char *l, t_node **lst);
int		make_new_token(t_node **lst, char *line, int i, int start);
int		make_new_token2(t_node **lst, char *line, int i, int start);
t_node	*make_node(char *str, int len, enum e_token type, enum e_state state);
t_node	*ft_lastlist(t_node *lst);
void	ft_add_back_list(t_node **lst, t_node *new);
int		ft_sizelist(t_node *lst);
void	print_list(t_node *lst);
void	free_tokens(t_node *lst);
int		dq_tokens(t_node **lst, char *line, int i);
int		sq_tokens(t_node **lst, char *line, int i);
char	*lexer_trim(char *str);

/* SYNTAX */
int		syntax_error(t_node **tokens);
int		syntax_head(t_node *head);
int		syntax_rd_in(t_node **h);
int		syntax_rd_out(t_node **h);
int		syntax_pipe(t_node **head);
int		qoute_check(t_node *tokens);

/* PARSER NODE */
t_pn	*make_node_parser(t_node *tokens);
t_pn	*ft_lastlist_parser(t_pn *lst);
void	ft_add_back_list_parser(t_pn **lst, t_pn *new);
//int		ft_sizelist_parser(t_pn **lst);
int		ft_sizelist_parser(t_pn *lst);
void	print_list_parser(t_pn *lst);
void	free_list(t_pn *lst);

/* PARSER LIST */
t_pl	*make_node_lparser(t_pn *small_list);
t_pl	*ft_lastlist_lparser(t_pl *lst);
void	ft_add_back_list_lparser(t_pl **lst, t_pl *new);
int		ft_sizelist_lparser(t_pl *lst);
void	print_list_lparser(t_pl **plist);
void	free_llist(t_pl **p_list);
void	close_fd(int fd_in, int fd_out);

/* REDIRECTION */
t_node	*rd_managment(t_node *tokens, t_pl **p_list, char ***env);
t_node	*rd_managment_utils(t_node *tokens, t_pl *node, char ***env);
t_node	*rd_in(t_node *tokens, t_pl *node, char ***env);
void	rd_in_utils(t_node *tokens, t_pl *node, char ***env);
t_node	*rd_out(t_node *tokens, t_pl *node);
t_node	*rd_atfirst_managment(t_node *tokens, t_pl **p_list, char ***env);
void	rd_atfirst_out(t_node *head, t_node *first_command, t_pl *node);
void	rd_atfirst_out_utils(t_node *head, t_pl *node);
void	rd_atfirst_in(t_node *head, t_node *f_cmnd, t_pl *node, char ***env);
void	rd_atfirst_in_utils(t_node *head, t_pl *node, char ***env);
t_node	*rd_makelist(t_node **tokens, t_pl **p_list, enum e_token rd_type);
t_node	*rd_ml_utils(t_node *tokens, t_node *first_command, t_pl **p_list);
t_node	*heredoc_expand(t_node *head, t_node *node);

/*REDIRECTION HEREDOC*/
void	rd_heredoc(t_pl *node, char ***env, t_node *lst);
void	rd_heredoc_utils(t_pl *node, char *line);
void	heredoc_without_command(t_node *head);
char	*heredoc_make_tokens(char *line, char ***env);
int		heredoc_find_env_var(char *variable, char **env);
char	*heredoc_find_variable(char *variable, enum e_token type, char ***env);
void	heredoc_expand_variable(t_node **lst, char ***env, int exit_status);
t_node	*heredoc_expand_split(t_node **head, char ***env);
char	*heredoc_make_tokens(char *line, char ***env);
char	*join_str_node(t_node *node);
void	heredoc_expansion(t_node **lst, char ***env);
void	heredoc_split_string_utils(t_node **exp_lst, char *string, int i);
void	heredoc_split_string(char *string_node, t_node **exp_lst);
t_node	*heredoc_expand_split(t_node **head, char ***env);
void	prepare_heredoc(t_pl *node, char **line, int *fork_pid);
void	prep_heredoc_nocom(t_node *head, char **line, \
char **del, int *fork_pid);
void	clear_heredoc_nocommand(int fork_pid, char *del);
void	clear_heredoc(t_pl *node, int fork_pid);

/* PARSER */
t_node	*make_parser(t_node **tokens, t_pl **p_list, char ***env);
t_node	*parser_utils(t_node *tokens, t_pl **p_list, char ***env);
t_node	*first_list_pl(t_node *tokens, t_pl **p_list, char ***env);
t_node	*special_last(t_node *tokens, t_node *head, t_pl **p_list);
t_node	*first_last(t_node *tokens, t_node *head, t_pl **p_list, char ***env);
void	qoute_trim(t_node *tokens);
void	combine_tokens(t_node *tokens);
void	combine_tokens_utils(t_node *tokens, t_node *temp);
t_node	*prepare_tokens(t_node **tokens);

/*	Expansion */
void	expansion(t_node **lst, char ***env, int exit_status);
char	*find_variable(char *variable, enum e_token type, char ***env);
t_node	*split_variable(t_node *lst);
t_node	*expand_split(t_node **head, char ***env, int exit_status);
void	expand_variable(t_node **lst, char ***env, int exit_status);
void	expand(t_node *head, t_node	**node);
void	expand_exit_code(t_node *head, int exit_status);
void	add_node_env(char *string, int i, int *start, t_node **exp_lst);
void	split_string(char *string_node, t_node **exp_lst);
void	add_exp_list(t_node *prev, t_node *head, char ***env, int exit_status);

/*	Execution */
void	execution(t_pl **p_list, char ***env, int *status);
void	*prepare(t_pl **parser, char ***env);
void	create_cmd_table(t_pl *parser);
void	redirection(t_pl *p_list, t_exec *data, int i);
int		redirect(t_pl *parser, int *status, int fd, bool STDIN);
int		redirection_error(t_exec *data, int i, int *status);
void	close_pipes(t_exec *data);
void	close_pipes_child(t_exec *data, int i);
void	waitpid_forks(t_exec *data, int *status);
int		create_fork_pipe(t_exec *data, t_pl *parser, int i);
int		error_exit(char *message, int error_no);
int		error_seterrno(char *message, char *message2, int error_no);
int		check_builtins(char **cmd_table, char ***env, int *status);
int		builtins_rd(t_exec **data, t_pl *parser, char ***env, int *status);
void	hide_signals(void);
void	show_signals(void);

/*	Built-ins */
int		echo_builtin(char **cmd_table);
int		cd_builtin(char **cmd_table, char ***env);
int		pwd_builtin(void);
int		env_builtin(char **env);
int		unset_builtin(char **cmd_table, char ***env);
int		export_builtin(char **cmd_table, char ***env);
int		exit_builtin(char **cmd_table, int status);

/*	Sub functions / Tools */
char	**copy_environment_list(char **env);
int		array_size(char **array);
void	*null_check(void *check);
int		find_env_var(char *variable, char **env);
int		find_value(char *string);
void	print_env(char ***env);
int		add_variable(char *string, char ***env);
void	free_data(t_exec *data, t_pl *parser);
void	put_env(char *string, char ***env);
int		check_variable(char **variable);
int		syntax_check(char *string);

/*	Signals */
void	signals_parent(void);
void	signals_child(void);
void	signals_heredoc(void);
void	parent_signint(int sig);
void	child_sigquit(int sig);
void	child_sigint(int sig);
void	heredoc_sigint(int sig);
void	signals_ignore(void);

#endif