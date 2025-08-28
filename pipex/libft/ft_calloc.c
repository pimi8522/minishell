/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:24:35 by adores            #+#    #+#             */
/*   Updated: 2025/04/14 09:54:04 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	mult;
	void	*ptr;

	if (nitems == 0 || size == 0)
		return (malloc(0));
	mult = nitems * size;
	if (nitems > INT_MAX / size)
		return (NULL);
	ptr = malloc(mult);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, mult);
	return (ptr);
}
/* #include <stdio.h>

int main(void)
{
	char *ptr;

	ptr = "Hello";
	printf("%s\n", ptr);
	
	ptr = (char*)ft_calloc(5,1);
	if(ptr)
		printf("PAssou\n");
	printf("%s", ptr);
} */
