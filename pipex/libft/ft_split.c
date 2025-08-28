/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:19:48 by adores            #+#    #+#             */
/*   Updated: 2025/04/17 17:01:14 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char sep)
{
	int	count;
	int	inword;
	int	i;

	count = 0;
	inword = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep)
		{
			if (inword == 0)
			{
				inword = 1;
				count++;
			}
		}
		else
			inword = 0;
		i++;
	}
	return (count);
}

static char	*malloc_word(char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
}

static void	ft_splitsplit(char **arr, char *str, char sep)
{
	int	i;
	int	word_i;

	word_i = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
		{
			arr[word_i] = malloc_word((char *)&str[i], sep);
			if (!arr[word_i])
			{
				ft_free(arr);
				return ;
			}
			word_i++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	arr[word_i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!arr)
		return (NULL);
	ft_splitsplit(arr, (char *)s, c);
	return (arr);
}
/*#include <stdio.h>

int	main(void)
{
	char const s[] = "   ";
	char c = ' ';
	int i = 0;
	char **res = ft_split(s, c);
	while(res[i])
	{
		printf("%s\n",res[i]);
		i++;
	}
}
*/
