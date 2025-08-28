/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:44:28 by adores            #+#    #+#             */
/*   Updated: 2025/04/14 13:22:22 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while ((i + j) < len && haystack[i + j] && needle[j]
			&& haystack[i + j] == needle[j])
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
/*#include <stdio.h>

int main(void)
{
	char *hay = "abcde";
	char *need = "cd";
	
	char *res = ft_strnstr(hay, need, 3);
	
	if (res)
		printf("Encontrado: %s\n", res);
	else
		printf("Não encontrado\n");
}*/
