/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/01 18:09:43 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	blah(void)
// {
// 	system("leaks minishell");
// }

char	*ft_readline(char *prompt, char **envp)
{
	char		*line;
	t_node		*lst;
	char		*new;
	t_pl		*p_list;
	char	**env;
	int		syntax_check;
	int		exit_status;
	
	// atexit(blah);
	signals_init();
	env = copy_environment_list(envp);
	p_list = NULL;
	syntax_check = 0;
	exit_status = 0;
	lst = NULL;
	while (1)
	{
		lst = NULL;
		unlink("here_doc");
		line = readline(prompt);
		new = ft_strtrim(line, " ");
		//if (!line || line[0] == '\0')
		if (!new)
		{
			//printf("\b\b \n");
			free(line);
			exit(1);
		}
		if (!new || new[0] == '\0')
		{
			free(line);
			free(new);
			line = readline(prompt);
			new = ft_strtrim(line, " ");
		}
		else
		{
			make_tokens(new, &lst);
			syntax_check = syntax_error(&lst);
				if (syntax_check == 0)
			{
				// if (lst == NULL)
				// 	printf("this is the head\n");
				expansion(&lst, &env, exit_status);
				lst = make_parser(&lst, &p_list, &env);
				//ft_putstr_fd("\n\n\n-----------MiniShell Output-------------\n", 1);
				execution(&p_list, &env, &exit_status);
				unlink("here_doc");
				ft_putstr_fd("Return code: ", 1);
				ft_putnbr_fd(exit_status, 1);
				ft_putstr_fd("\n-----------MiniShell Output-------------\n", 1);
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
	// atexit(blah);
	char *line;
	argc = 0;
	argv[0] = NULL;
	line = ft_readline("minishell~>", envp);
	return (0);
}
