/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:29:51 by adores            #+#    #+#             */
/*   Updated: 2025/04/14 10:04:50 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (i < dstsize - dest_len - 1 && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/* #include <stdio.h>

int main(void)
{
	char dest[5] = "abc";
	char src[] = "defg";
	size_t size = 5;

	printf("Tamanho final: %zu\n", ft_strlcat(dest, src, size));
	printf("Resultado: %s\n", dest);
} */