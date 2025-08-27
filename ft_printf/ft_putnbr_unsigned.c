/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:37:56 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/05 12:01:38 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(uintptr_t nb, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if ((long)nb < base)
		return (ft_putchar(symbols[nb]));
	else
	{
		count = ft_putnbr_unsigned(nb / base, base);
		return (count + ft_putnbr_unsigned(nb % base, base));
	}
	return (count);
}
