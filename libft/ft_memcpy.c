/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:58:34 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 14:15:08 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dest, const void	*source, size_t	num)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;
	size_t			i;

	i = 0;
	if (!dest && !source)
		return (dest);
	destptr = (unsigned char *) dest;
	srcptr = (unsigned char *) source;
	while (i < num)
	{
		destptr[i] = srcptr[i];
		i++;
	}
	return (dest);
}
