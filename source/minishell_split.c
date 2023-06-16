/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 12:54:12 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/06/16 15:23:28 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_checkquote(char *s)
// {
// 	int	i;

// 	i = ft_strlen(s) - 1;
// 	if (s[i] == '\'' || s[i] == '\"')
// 		return (0);
// 	return (-1);
// }

int	ft_checkline(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>'
		|| s[i] == '$' || s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	count_words_msh(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while(s[i] != '\0')
	{
		if (s[i] == ' ')
			i++;
		else
		{
			words++;
			if (s[i] == '\'')
			{
				printf("sq i = %d\n", i);
				i++;
				while(s[i] != '\'' && s[i] != '\0')
					i++;
				i++;
			}
			else if (s[i] == '\"')
			{
				printf("dq i = %d\n", i);
				i++;
				while(s[i] != '\"' && s[i] != '\0')
					i++;
				i++;
			}
			else if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && (s[--i] != ' ' || (s[++i] != ' ' && s[++i] != '\0')))//(((s[--i] != ' ' || (s[++i] != ' ' && s[++i] != '\0')) || (s[--i] != ' ' && (s[++i] != ' ' && s[++i] != '\0')))))
			{
				printf("pipe i now= %d\n", i);
				words++;
				i++;
				printf("and pipe i now= %d\n", i);
			}
			while(s[i] != '\0' && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
				i++;
		}
	}
	return (words);
}
int	count_words(char const	*s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (words);
}

// int	ft_free(char	**new, int words)
// {
// 	if (!new[words])
// 	{
// 		while (words >= 0)
// 		{
// 			free (new[words]);
// 			words--;
// 		}
// 		free (new);
// 		return (0);
// 	}
// 	return (0);
// }

// char	**count_arrays(char	*s, char c, char **new)
// {
// 	unsigned int	i;
// 	int				words;
// 	unsigned int	start;
// 	size_t			len;

// 	i = 0;
// 	words = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			i++;
// 		else
// 		{
// 			start = i;
// 			while (s[i] != '\0' && s[i] != c)
// 				i++;
// 			len = (size_t)(i - start);
// 			new[words] = ft_substr(s, start, len);
// 			ft_free(new, words);
// 			words++;
// 		}
// 		new[words] = NULL;
// 	}
// 	return (new);
// }

// char	**ft_newsplit(char *s)
// {
// 	char	**command;
// 	int		j;
// 	int		start;
// 	char	quote;

// 	start = 0;
// 	j = 0;
// 	command = ft_calloc(3, sizeof(char *));
// 	while (s[j] != ' ' && s[j] != '\0')
// 		j++;
// 	quote = s[j + 1];
// 	command[0] = ft_calloc(j + 1, sizeof(char));
// 	while (s[j] != '\0' && start < j)
// 	{
// 		command[0][start] = s[start];
// 		start++;
// 	}
// 	start = 0;
// 	j = j + 2;
// 	command[1] = ft_calloc(ft_strlen(ft_strchr(s, quote)), sizeof(char));
// 	while (s[j + 1] != '\0')
// 		command[1][start++] = s[j++];
// 	if (command[0] == NULL || command[1] == NULL)
// 		ft_freeall(command);
// 	return (command);
// }

// char	**ft_split(char *s, char c)
// {
// 	char	**new;
// 	int		i;

// 	i = 0;
// 	if (ft_checkline(s) == 0)
// 	{
// 		new = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
// 		if (!new)
// 			return (NULL);
// 		if (s[i] == '\0')
// 		{
// 			new[0] = NULL;
// 			return (new);
// 		}
// 		return (count_arrays(s, c, new));
// 	}
// 	else
// 		return (ft_newsplit(s));
// }