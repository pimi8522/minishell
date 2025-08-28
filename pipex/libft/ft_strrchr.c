/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:47:35 by adores            #+#    #+#             */
/*   Updated: 2025/04/17 16:32:49 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	if (str[i] == (char)c)
		return ((char *)(str + i));
	return (NULL);
}
/* int	main(void)
{
	const char str[] = "ohote";
	printf("%s\n", ft_strrchr(str, 'o'));
} */
