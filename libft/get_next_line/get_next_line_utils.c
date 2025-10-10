/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:13:46 by adores            #+#    #+#             */
/*   Updated: 2025/05/08 15:31:37 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlengnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoingnl(char const *s1, char const *s2)
{
	char	*newstr;
	int		newstrlen;
	int		i;
	int		j;

	newstrlen = ft_strlengnl(s1) + ft_strlengnl(s2);
	newstr = malloc(sizeof(char) * (newstrlen + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] && s2[j] != '\n')
		newstr[i++] = s2[j++];
	if (s2 && s2[j] == '\n')
		newstr[i++] = '\n';
	newstr[i] = '\0';
	free((char *)s1);
	return (newstr);
}

int	ft_bufferreset(char *buffer)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	j = 0;
	flag = 0;
	while (buffer[i])
	{
		if (flag == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			flag = 1;
		buffer[i] = 0;
		i++;
	}
	return (flag);
}

/* World	/n Hello

00000 0 Hello

j = 0
i = 7

H0000 0 Hello

j = 1

H0000 0 0ello
i = 8

Hello 0 00000 */