/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 18:24:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/06 13:56:15 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	blah(void)
// {
// 	system("leaks minishell");
// }
void	free_all(char *line, char *new, t_node *lst, t_pl **p_list)
{
	free(new);
	free(line);
	free_tokens(lst);
	free_llist(p_list);
}

char	*ft_readline(char *prompt, char **envp)
{
	char	*line;
	t_node	*lst;
	char	*new;
	t_pl	*p_list;
	char	**env;
	int		syntax_check;
	int		exit_status;

	signals_init();
	env = copy_environment_list(envp);
	p_list = NULL;
	exit_status = 0;
	while (1)
	{
		lst = NULL;
		unlink("here_doc");
		line = readline(prompt);
		new = ft_strtrim(line, " ");
		if (!new)
		{
			free(line);
			exit(1);
		}
		if (!new || new[0] == '\0')
		{
			free(line);
			free(new);
			continue ;
		}
		else
		{
			make_tokens(new, &lst);
			syntax_check = syntax_error(&lst);
			if (syntax_check == 0)
			{
				expansion(&lst, &env, exit_status);
				lst = make_parser(&lst, &p_list, &env);
				execution(&p_list, &env, &exit_status);
				unlink("here_doc");
			}
			add_history(line);
		}
		free_all(line, new, lst, &p_list);
		//system("leaks -quiet minishell");
	}
	return (line);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	argc = 0;
	argv[0] = NULL;
	line = ft_readline("minishell~>", envp);
	return (0);
}
