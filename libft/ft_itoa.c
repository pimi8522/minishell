/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:51:12 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/21 12:50:26 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_intlen(long n)
{
	long	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*numstr;
	int		intlen;
	long	num;

	num = n;
	if (num == 0)
		return (ft_strdup("0"));
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	intlen = ft_intlen(num);
	numstr = (char *)malloc(sizeof(char) * (intlen + 1));
	if (!numstr)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		numstr[0] = '-';
	}
	numstr[intlen] = '\0';
	while (num != 0)
	{
		numstr[--intlen] = (num % 10) + '0';
		num = num / 10;
	}
	return (numstr);
}
