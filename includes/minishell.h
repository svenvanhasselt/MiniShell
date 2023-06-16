/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:33:17 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/16 14:19:19 by psadeghi      ########   odam.nl         */
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
	IN_DOUBLEQ,
	IN_SINGLEQ,
	NORMAL,
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
int		ft_checkline(char *s);
int		count_words_msh(char *s);
int		count_words(char const	*s, char c);

#endif