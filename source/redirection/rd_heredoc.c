/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_heredoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:36:54 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/31 18:05:56 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_find_env_var(char *variable, char **env)
{
	int			i;
	char		*new_variable;
	char		*after_trim;

	after_trim = ft_strtrim(variable, "\n");
	new_variable = ft_strjoin(after_trim, "=");
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], new_variable, ft_strlen(new_variable)) ||\
		!strncmp(env[i], after_trim, ft_strlen(after_trim)))
			return (free(new_variable), i);
		i++;
	}
	free(new_variable);
	return (-1);
}

char	*heredoc_find_variable(char *variable, enum e_token type, char ***env)
{
	int		var_set;
	char	*value;

	var_set = heredoc_find_env_var(variable, (*env));
	if (var_set >= 0)
	{
		value = null_check(ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
		free(variable);
		return (value);
	}
	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
		return (variable);
	else if (type == EXP)
		return (NULL);
	return (NULL);
}

void	heredoc_expand_variable(t_node **lst, char ***env, int exit_status)
{	
	t_node	*head;
	t_node	*prev;

	head = *lst;
	prev = head;
	while (head)
	{
		if (head->type == ENV)
		{
			if (!ft_strncmp(head->str, "?", ft_strlen(head->str)))
				head->str = null_check(ft_strdup(null_check(ft_itoa(exit_status)))); //LEAK?
			else if (*lst == head)
			{
				head->str = heredoc_find_variable(head->str, head->type, env);
				if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
					*lst = split_variable(head);
			}
			else
			{
				head->str = find_variable(head->str, head->type, env);
				if (ft_strnstr(head->str, " ", ft_strlen(head->str)))
					prev = split_variable(head);
			}
		}
		prev = head;
		head = head->next;
	}
}

t_node	*heredoc_expand_split(char *string, char ***env)
{
	int		i;
	int		start;
	int		len;
	char	*split_str;
	t_node	*exp_lst;
	t_node	*node;

	exp_lst = NULL;
	len = (int)ft_strlen(string);
	start = -1;
	i = 0;
	split_str = NULL;
	while (i <= len)
	{
		if ((string[i] != '$' && string[i] != ' ') && (start < 0))
			start = i;
		else if (((string[i] == '$' || string[i] == ' ' || i == (int)len) && start >= 0))
		{
			split_str = null_check(ft_substr(string, start, i - start));
			node = make_node(split_str, ft_strlen(split_str), WORD, IN_DOUBLEQ);
			if (start - 1 >= 0 && string[start - 1] == '$')
				node->type = ENV;
			printf("1\n");
			ft_add_back_list(&exp_lst, node);
			printf("2\n");
			start = -1;
		}
		if (string[i] == '$' && (string[i + 1] == '\0' || string[i + 1] == ' '))
			ft_add_back_list(&exp_lst, make_node("$", 1, ENV, IN_DOUBLEQ));
		if (string[i] == ' ')
			ft_add_back_list(&exp_lst, make_node(" ", 1, SPC, NORMAL));
		i++;
	}
	heredoc_expand_variable(&exp_lst, env, 0);
	return (exp_lst);
}

void	heredoc_without_command(t_node *head, char ***env)
{
	char	*line;
	char	*del;
	t_node	*new;

	line = NULL;
	del = ft_strjoin(head->str, "\n");
	while (1)
	{
		line = get_next_line(1);
		if (head->state != IN_DOUBLEQ)
			new = heredoc_expand_split(line, env);
		if (line && \
		ft_strncmp(line, del, ft_strlen(del)) != 0)
			free(line);
		if (!line || \
		ft_strncmp(line, del, ft_strlen(del)) == 0)
		{
			free(line);
			break ;
		}
	}
	free(del);
	return ;
}

void	rd_heredoc(t_pl *node, char ***env, t_node *lst)
{
	char	*line;
	t_node	*new;

	line = NULL;
	unlink("here_doc");
	close(node->fd_in);
	node->fd_in = open("here_doc", O_CREAT | O_RDWR | O_EXCL, 0777);
	while (1)
	{
		line = get_next_line(1);
		if (lst->state != IN_DOUBLEQ)
			new = heredoc_expand_split(line, env);
		if (line && \
		ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) != 0)
		{
			write(node->fd_in, line, ft_strlen(line));
			free(line);
		}
		if (!line || \
		ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter)) == 0)
			break ;
	}
	close(node->fd_in);
	node->fd_in = open("here_doc", O_RDONLY);
	node->rd_in_heredoc = false;
}
