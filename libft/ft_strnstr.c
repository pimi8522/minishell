/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:08:26 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 16:01:59 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (little[0] == '\0' || ft_strlen(little) == 0)
		return ((char *)big);
	while ((big[i] != '\0') && (i < len))
	{
		i2 = 0;
		while (big[i + i2] == little[i2] && (i + i2) < len)
		{
			if (little[i2 + 1] == '\0')
				return ((char *)big + i);
			i2++;
		}
		i++;
	}
	return (NULL);
}
