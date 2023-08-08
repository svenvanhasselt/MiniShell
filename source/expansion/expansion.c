/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 18:26:09 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/08 17:53:51 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_word(t_node *head, char ***env, int exit_status)
{
	int	i;
	int	var_set;

	if (ft_strncmp(head->str, "$?", 2) == 0)
	{
		free(head->str);
		head->str = ft_strdup(ft_itoa(exit_status));
	}
	else
	{
		var_set = find_env_var((head->str + 1), (*env));
		if (var_set < 0)
		{
			free(head->str);
			head->str = ft_strdup("");
		}
		else
		{
			free(head->str);
			i = find_value((*env)[var_set]);
			head->str = ft_strdup((*env)[var_set] + i + 1);
		}
	}
}

void	add_nodes(char **split_variable, t_node *head)
{
	int	i;
	t_node *split_token;

	i = 1;
	while (split_variable[i])
	{
		split_token = make_node(split_variable[i], ft_strlen(split_variable[i]), WORD, NORMAL);
		if (split_variable[i + 1] == NULL)
		{
			printf("WOohOo: %s\n", split_token->str);
			split_token->state = IN_DOUBLEQ;
		}
		split_token->next = head->next;
		head->next = split_token;
		//free(split_token);
		head = head->next;
		i++;
	}
}

char	*word_split(char **new_str, t_node *head)
{
	char	**split_variable;

	if (new_str && ft_strnstr(*new_str, " ", ft_strlen(*new_str)))
	{
		split_variable = null_check(ft_split(*new_str, ' '));
		free(*new_str);
		*new_str = null_check(ft_strtrim(split_variable[0], "\""));
		add_nodes(split_variable, head);
		return (split_variable[0]);
	}
	return (*new_str);
}

char	*new_str(t_node *head, char ***env, int len, int exit_status)
{
	int		i;
	int		j;
	char	*new_str;
	char	*variable;

	new_str = null_check(malloc((len + 1) * sizeof(char)));
	i = 0;
	j = 0;
	while (head->str[i])
	{
		if (head->str[i] == '$')
		{
			i++;
			variable = find_word(head, env, &i);
			copy_variable(&new_str, variable, &j);
			word_split(&new_str, head);

		}
		else
		{
			new_str[j] = head->str[i];
			j++;
			i++;
		}
	}
	new_str[j] = '\0';
	free(head->str);
	head->str = new_str;
	return (new_str);
}

void	expand_quotes(t_node *head, char ***env, int exit_status)
{

	if (!ft_strnstr(head->str, "$", head->len))
		return ;
	if (ft_strncmp(head->str, "$?", 2) == 0)
	{
		free(head->str);
		head->str = ft_strdup(ft_itoa(exit_status));
	}
	else
	{
		new_str(head, env, new_length(head, env), exit_status); // LEAKES?
		printf("TEST: %s\n", head->str);		
		head->state = NORMAL;
	}
}

void	expansion(t_node **lst, char ***env, int exit_status)
{
	t_node	*head;

	head = *lst;
	while (head)
	{
		// if (head->type == ENV)
		// 	expand_word(head, env, exit_status);
		if (head->type == ENV || head->state == IN_DOUBLEQ)
			expand_quotes(head, env, exit_status);
		head = head->next;
	}
}
