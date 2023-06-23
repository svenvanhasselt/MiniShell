/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/23 11:46:20 by psadeghi      ########   odam.nl         */
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

int		main();
char	*ft_readline(char *prompt);
void	check_line(char *line, t_node **lst);
t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state);
t_node	*ft_lastlist(t_node *lst);
void	ft_add_back_list(t_node **lst, t_node *new);
int		ft_sizelist(t_node *lst);
void	print_list(t_node *lst);
// int		ft_checkline(char *s);
// int		count_words_msh(char *s);
// int		count_words(char const	*s, char c);
// char	**count_arrays_msh(char	*s, char **new);
// int		ft_free(char	**new, int words);

#endif