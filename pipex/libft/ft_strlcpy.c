/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:33:35 by adores            #+#    #+#             */
/*   Updated: 2025/04/19 14:15:30 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (!src)
		return (0);
	while ((dstsize - 1) > i && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/* #include <stdio.h>

int main(void)
{
	char *source = "HELLOOOOO";
	char dest[25];
	size_t copied;

    copied = ft_strlcpy(dest, source, 5);
    printf("Resultado: %s, len = %zu\n", dest, copied);
} */
