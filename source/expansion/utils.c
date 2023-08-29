// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   utils.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: sven <sven@student.42.fr>                    +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/02 12:36:31 by svan-has      #+#    #+#                 */
// /*   Updated: 2023/08/16 17:32:54 by svan-has      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include <minishell.h>

// char	*find_variable(char *variable, enum e_token type, char ***env)
// {
// 	int		var_set;
// 	char	*value;

// 	printf("var: %s\n", variable);
// 	var_set = find_env_var(variable, (*env));
// 	if (var_set >= 0)
// 	{
// 		value = null_check(ft_strdup(((*env)[var_set] + find_value((*env)[var_set]) + 1)));
// 		free(variable);
// 		return (value);
// 	}
// 	if (!ft_strncmp(variable, "$", ft_strlen(variable)))
// 		return (variable);
// 	else if (type == EXP)
// 		return (NULL);
// 	return (NULL);
// }

// t_node	*split_variable(t_node *lst)
// {
// 	int		i;
// 	char	**split_str;
// 	t_node	*word_split;
// 	t_node	*node;


// 	word_split = NULL;
// 	split_str = null_check(ft_split(lst->str, ' '));
// 	free(lst->str);
// 	i = 0;
// 	while (split_str[i])
// 	{
// 		node = make_node(split_str[i], ft_strlen(split_str[i]), lst->type, EXP);
// 		ft_add_back_list(&word_split, node);
// 		i++;
// 	}
// 	node = ft_lastlist(word_split);
// 	node->next = lst->next;
// 	free(lst);
// 	return (word_split);
// }