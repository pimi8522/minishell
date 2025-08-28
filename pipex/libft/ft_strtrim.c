/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:36:28 by adores            #+#    #+#             */
/*   Updated: 2025/04/17 16:56:27 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*newstr;

	if (!s1 || ! set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_in_set(set, s1[end - 1]))
		end--;
	newstr = malloc(sizeof(char) * (end - start + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		newstr[i] = s1[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
/* #include <stdio.h>
int main(void)
{
	char const str[50] = "aaaaaaaaaaaabxxxxxHallxobbbbbbaaaaa";
	char const set[] = "abx";
	printf("%s\n", ft_strtrim(str, set));
} */