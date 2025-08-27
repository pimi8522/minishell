/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:00:41 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 14:16:55 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < num)
	{
		temp[i] = (unsigned char) value;
		i++;
	}
	return (ptr);
}
