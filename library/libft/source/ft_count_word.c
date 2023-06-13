/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_word.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 13:28:53 by svan-has      #+#    #+#                 */
/*   Updated: 2023/03/19 13:29:37 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_word(char const *s, char c)
{
	int	switch_num;
	int	w_count;

	switch_num = 0;
	w_count = 0;
	while (*s)
	{
		if (*s != c && switch_num == 0)
		{
			switch_num = 1;
			w_count++;
		}
		if (*s == c)
			switch_num = 0;
		s++;
	}
	return (w_count);
}
