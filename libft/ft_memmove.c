/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:58:18 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 14:15:40 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*tempsrc;
	char	*tempdest;
	size_t	i;

	i = 0;
	tempsrc = (char *) src;
	tempdest = (char *) dest;
	if (tempdest > tempsrc)
	{
		while (len > 0)
		{
			len--;
			tempdest[len] = tempsrc[len];
		}
	}
	else
	{
		while (i < len)
		{
			tempdest[i] = tempsrc[i];
			i++;
		}
	}
	return (dest);
}
