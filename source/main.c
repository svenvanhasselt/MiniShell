/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:09:03 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/21 18:45:50 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	blah(void)
// {
// 	system("leaks minishell");
// }

char	*ft_readline(char *prompt)
{
	char		*line;
	t_node		*lst;
	char		*new;
	t_pl		*p_list;
	extern char	**environ;
	char	**env;
	int		syntax_check;
	int		exit_status;
	
	// atexit(blah);
	signals_init();
	env = copy_environment_list(environ);
	p_list = NULL;
	syntax_check = 0;
	exit_status = 0;
	lst = NULL;
	while (1)
	{
		printf("each time\n");
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
			printf("line = \"%s\"\n", line);
			// printf("new = .%s.\n", new);
			// printf("compare new and line = %d\n", strcmp(new, line));
			make_tokens(new, &lst);
			printf("after make tokens\n");
			syntax_check = syntax_error(&lst);
			printf("this is the syntax check %d\n", syntax_check);
			if (syntax_check == 0)
			{
				if (lst == NULL)
					printf("this is the head\n");
				//expansion(&lst, &env, exit_status);
				lst = make_parser(&lst, &p_list);
				printf("got here!\n");
				//printf("pointer before = %p\n", p_list->lst);
				// ft_putstr_fd("\n\n\n-----------MiniShell Output-------------\n", 1);
				exit_status = execution(&p_list, &env, exit_status);
				//printf("pointer after = %p\n", p_list->lst);
				//free_llist(&p_list);
				unlink("here_doc");
				printf("2 got here!\n");
				// ft_putstr_fd("Return code: ", 1);
				// ft_putnbr_fd(exit_status, 1);
				// ft_putstr_fd("\n-----------MiniShell Output-------------\n", 1);
			}
			// ft_putstr_fd("\n\n\n-----------Bash Output-------------\n", 1);
			// char *bash = ft_strjoin(line, " && echo Return code: $?");
			// system(bash);
			// ft_putstr_fd("-----------Bash Output-------------", 1);
			// ft_putstr_fd("\n\n\n", 1);
			// free(bash);
			add_history(line);
			printf("3 got here!\n");
			// free_llist(&p_list);
			// free_tokens(&lst);
		}
		free(new);
		free(line);
		// printf("this is the parser list after free token:\n");
		// print_list_lparser(&p_list);
		// printf("make parser thats it\n");
		// printf("4 got here!\n");
		free_tokens(lst);
		// printf("after free tokens\n");
		free_llist(&p_list);
		// printf("5 got here!\n");
		// printf("this is the parser list before free token:\n");
		// print_list_lparser(&p_list);
		// printf("make parser thats it\n");
		// printf("this is the parser list after free in main:\n");
		// print_list_lparser(&p_list);
		// printf("make parser thats it\n");
		system("leaks minishell");
	}
	return (line);
}

int	main(void)
{
	char *line;

	line = ft_readline("minishell~>");
	return (0);
}
