/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:38:25 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 14:21:22 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	in_word;
	int	num_words;

	i = 0;
	in_word = 0;
	num_words = 0;
	while (str[i])
	{
		if (str[i] != c && in_word == 0)
		{
			in_word = 1;
			num_words++;
		}
		else if (str[i] == c)
			in_word = 0;
		i++;
	}
	return (num_words);
}

static char	*get_word(char const *str, char c, int *x)
{
	int		start;
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (str[*x] && str[*x] == c)
		(*x)++;
	start = *x;
	while (str[*x + len] && str[*x + len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[len] = '\0';
	*x += len;
	return (word);
}

static void	free_all(char **result, int y)
{
	while (y >= 0)
	{
		free(result[y]);
		y--;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;
	int		x;
	int		y;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	x = 0;
	y = 0;
	while (y < count)
	{
		result[y] = get_word(s, c, &x);
		if (!result[y])
		{
			free_all(result, y - 1);
			return (NULL);
		}
		y++;
	}
	result[y] = NULL;
	return (result);
}
