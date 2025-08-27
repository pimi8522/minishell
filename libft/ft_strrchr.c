/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:48:25 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/22 13:41:43 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	if (character == '\0')
		return ((char *)&str[i]);
	while (i >= 0)
	{
		if (str[i] == (char)character)
			return ((char *)&str[i]);
		if (i == 0)
			break ;
		i--;
	}
	return (NULL);
}
