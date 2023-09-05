/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 18:24:48 by svan-has      #+#    #+#                 */
/*   Updated: 2023/09/05 17:45:11 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_heredoc = 0;

char	*ft_readline(char *prompt, char **envp)
{
	char		*line;
	t_node		*lst;
	char		*new;
	t_pl		*p_list;
	char	**env;
	int		syntax_check;
	int		exit_status;
	
	signals_parent();
	env = copy_environment_list(envp);
	p_list = NULL;
	syntax_check = 0;
	exit_status = 0;
	lst = NULL;
	while (1)
	{
		g_heredoc = 0;
		signals_parent();
		lst = NULL;
		unlink("here_doc");
		line = readline(prompt);
		new = ft_strtrim(line, " ");
		if (!new)
		{
			free(line);
			exit(1);
		}
		else if (new[0] == '\0')
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
				if (g_heredoc < 2)
					execution(&p_list, &env, &exit_status);
				unlink("here_doc");
				// ft_putstr_fd("Return code: ", 1);
				// ft_putnbr_fd(exit_status, 1);
				// ft_putstr_fd("\n-----------MiniShell Output-------------\n", 1);
			}
			add_history(line);
		}
		free(new);
		free(line);
		free_tokens(lst);
		free_llist(&p_list);
		system("leaks -quiet minishell");
	}
	return (line);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	argc = 0;
	argv[0] = NULL;
	line = ft_readline("minishell~>", envp);
	return (0);
}
