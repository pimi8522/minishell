/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_basex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:42:47 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/05 12:01:01 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_basex(unsigned int n, int base, int caps)
{
	int			count;
	const char	*symbols;
	const char	*symbolsupper;

	symbols = "0123456789abcdef";
	symbolsupper = "0123456789ABCDEF";
	count = 0;
	if (base < 2 || base > 16)
		return (0);
	if (n >= (unsigned int)base)
		count += ft_putnbr_basex(n / base, base, caps);
	if (caps == 0)
		count += ft_putchar(symbols[n % base]);
	else
		count += ft_putchar(symbolsupper[n % base]);
	return (count);
}
