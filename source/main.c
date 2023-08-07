/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/07 14:46:02 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	blah(void)
// {
// 	system("leaks minishell");
// }
char	*ft_readline(char *prompt)
{
	char	*line;
	t_node	*lst;
	char	*new;
	t_parser_list *p_list;
	extern char	**environ;
	char	**env;
	int		syntax_check;
	
	// atexit(blah);
	env = copy_environment_list(environ);
	p_list = NULL;
	syntax_check = 0;
	
	lst = NULL;
	while(1)
	{
		printf("each time\n");
		unlink("here_doc");
		free_llist(&p_list);
		free_tokens(&lst);
		line = readline(prompt);
		new = ft_strtrim(line, " ");
		//if (!line || line[0] == '\0')
		if (!new || new[0] == '\0')
		{
			line = readline(prompt);
			new = ft_strtrim(line, " ");
		}
		else
		{
			printf("line = \"%s\"\n", line);
			printf("new = .%s.\n", new);
			printf("compare new and line = %d\n", strcmp(new, line));
			make_tokens(new, &lst);
			syntax_check = syntax_error(&lst);
			printf("this is the syntax check %d\n", syntax_check);
			if (syntax_check == 0)
			{
				if (lst == NULL)
					printf("this is the head\n");
				expansion(&lst, &env);
				make_parser(&lst, &p_list);
				ft_putstr_fd("\n\n\n-----------MiniShell Output-------------\n", 1);
				int ret = execution(&p_list, &env);
				unlink("here_doc");
				ft_putstr_fd("Return code: ", 1);
				ft_putnbr_fd(ret, 1);
				ft_putstr_fd("\n-----------MiniShell Output-------------\n", 1);
			}
			ft_putstr_fd("\n\n\n-----------Bash Output-------------\n", 1);
			char *bash = ft_strjoin(line, " && echo Return code: $?");
			system(bash);
			ft_putstr_fd("-----------Bash Output-------------", 1);
			ft_putstr_fd("\n\n\n", 1);
			free(bash);
			add_history(line);
		}
	}
	return (line);
}

int	main()
{
	char *line;

	line = ft_readline("minishell~>");
	return(0);
}
