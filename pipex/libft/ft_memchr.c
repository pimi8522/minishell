/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:47:01 by adores            #+#    #+#             */
/*   Updated: 2025/04/14 09:58:58 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temps;
	unsigned char	tempc;
	size_t			i;

	temps = (unsigned char *)s;
	tempc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (temps[i] == tempc)
			return ((void *)&temps[i]);
		i++;
	}
	return (NULL);
}
/* #include <stdio.h>

int main(void)
{
	char string[] = "HELLO WORLD";
	char *res = ft_memchr(string, 'O', 4);
	if (res)
		printf("RES: %s\n", res);
	else
		printf("NO RES\n");
} */