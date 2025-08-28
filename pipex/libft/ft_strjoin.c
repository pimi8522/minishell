/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:40 by adores            #+#    #+#             */
/*   Updated: 2025/04/22 13:52:40 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	newstrlen;
	int		i;
	int		j;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	newstrlen = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	newstr = (char *)malloc(sizeof(char) * newstrlen);
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		newstr[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		newstr[j++] = s2[i++];
	newstr[j] = '\0';
	return (newstr);
}
/* #include <stdio.h>
int main(void)
{
	char str1[] = "HELLO ";
	char str2[] = "WORLD";
	printf("%s\n", ft_strjoin(str1, str2));
} */