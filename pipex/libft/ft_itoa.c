/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:17:13 by adores            #+#    #+#             */
/*   Updated: 2025/04/22 13:58:20 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_countn(long n)
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
	intlen = ft_countn(num);
	numstr = (char *)malloc(sizeof(char) * (intlen + 1));
	if (!numstr)
		return (NULL);
	if (num == 0)
		numstr[0] = '0';
	if (num < 0)
	{
		num = -num;
		numstr[0] = '-';
	}
	numstr[intlen] = '\0';
	while (num != 0)
	{
		numstr[--intlen] = (num % 10) + 48;
		num = num / 10;
	}
	return (numstr);
}
/* #include <stdio.h>
int main(void)
{
	int i = -10;
	printf("%s\n", ft_itoa(i));
} */
