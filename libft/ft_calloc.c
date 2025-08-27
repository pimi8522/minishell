/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:15:28 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 12:45:56 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mult;

	if (count == 0 || size == 0)
		return (malloc(0));
	mult = count * size;
	if (count > INT_MAX / size)
		return (NULL);
	ptr = malloc(mult);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, mult);
	return (ptr);
}
