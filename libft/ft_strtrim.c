/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:10:48 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 15:26:41 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_target(const char *set, char c)
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
	while (s1[start] && is_target(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_target(set, s1[end - 1]))
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
