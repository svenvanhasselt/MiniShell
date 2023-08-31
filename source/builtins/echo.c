/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:47:29 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/31 11:38:05 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(char **cmd_table, int arguments, int *index)
{
	int	i;
	int return_value;

	i = 1;
	if (arguments >= 2 && !ft_strncmp(cmd_table[i], "-n", 1))
		return_value = 1;
	else
		return_value = 0;
	i += return_value;
	while (cmd_table[i])
	{
		if (arguments >= 2 && !ft_strncmp(cmd_table[i], "-n", 1))
			i++;
		else
			break;
	}
	*index = i;
	return (return_value);
}

int	echo_builtin(char **cmd_table)
{
	int	i;
	int	arguments;
	int	new_line;

	arguments = array_size(cmd_table);
	i = 1;
	new_line = check_newline(cmd_table, arguments, &i);
	while (i < arguments)
	{
		if (printf("%s", cmd_table[i]) < 0)
			return (1);
		if (cmd_table[i + 1] && printf(" ") < 0)
			return (1);
		i++;
	}
	if (!new_line && printf("\n") < 0)
		return (1);
	return (0);
}
