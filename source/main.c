/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 18:24:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/11 12:56:25 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signals = 0;

void	free_all(char *line, char *new, t_node *lst, t_pl **p_list)
{
	free(new);
	free(line);
	free_tokens(lst);
	free_llist(p_list);
}

void	parse_execute(t_node **lst, t_pl **p_list, char ***env, \
int *exit_status)
{
	int	syntax_check;

	syntax_check = syntax_error(lst);
	if (syntax_check == 0)
	{
		expansion(lst, env, *exit_status);
		*lst = make_parser(lst, p_list, env);
		show_signals();
		if (g_signals < 2)
			execution(p_list, env, exit_status);
		else
			*exit_status = 1;
		unlink("here_doc");
	}
}

int	prompt_init(t_node	**lst, char	**line, char **new)
{
	g_signals = 0;
	signals_parent();
	*lst = NULL;
	unlink("here_doc");
	*line = readline("minishell~>");
	add_history(*line);
	*new = lexer_trim(*line);
	if (!*new)
	{
		free(*line);
		exit(0);
	}
	else if (*new[0] == '\0')
	{
		free(*new);
		free(*line);
		return (0);
	}
	return (1);
}

void	main_init(int argc, char *argv[], t_mdata **main, char **envp)
{
	(*main) = null_check(malloc(1 * sizeof(t_mdata)));
	(*main)->env = copy_environment_list(envp);
	(*main)->p_list = NULL;
	(*main)->exit_status = 0;
	argc = 0;
	argv[0] = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mdata	*main; 

	main_init(argc, argv, &main, envp);
	while (1)
	{
		if (!prompt_init(&main->lst, &main->line, &main->new))
			continue ;
		else
		{
			make_tokens(main->new, &main->lst);
			parse_execute(&main->lst, &main->p_list, &main->env, \
			&main->exit_status);
		}
		free_all(main->line, main->new, main->lst, &main->p_list);
		system("leaks minishell");
	}
	return (0);
}
