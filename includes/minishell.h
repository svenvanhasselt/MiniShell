/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/12 11:57:23 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include "libft.h"
# include <errno.h>

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
}				t_parser_list;

int		main_paris();
char	*ft_readline(char *prompt);
void	check_line(char *line, t_node **lst);
t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state);
t_node	*ft_lastlist(t_node *lst);
void	ft_add_back_list(t_node **lst, t_node *new);
int		ft_sizelist(t_node *lst);
void	print_list(t_node *lst);

//--------Parser Node functions
t_parser_node	*make_node_parser(t_node *tokens);
t_parser_node	*ft_lastlist_parser(t_parser_node *lst);
void			ft_add_back_list_parser(t_parser_node **lst, t_parser_node *new);
int				ft_sizelist_parser(t_parser_node *lst);
void			print_list_parser(t_parser_node *lst);
//-----Parser list functions
t_parser_list	*make_node_lparser(t_parser_node *small_list);
t_parser_list	*ft_lastlist_lparser(t_parser_list *lst);
void			ft_add_back_list_lparser(t_parser_list **lst, t_parser_list *new);
int				ft_sizelist_lparser(t_parser_list *lst);
void			print_list_lparser(t_parser_list **plist);
//-----Parser
void	make_parser(t_node **tokens);
// int		ft_checkline(char *s);
// int		count_words_msh(char *s);
// int		count_words(char const	*s, char c);
// char	**count_arrays_msh(char	*s, char **new);
// int		ft_free(char	**new, int words);

#endif