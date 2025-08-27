/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:38:04 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/22 13:40:30 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int character)
{
	int	i;

	i = 0;
	if (!str && ft_isascii(character) == 0)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)character)
			return ((char *)&str[i]);
		i++;
	}
	if (character == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
