/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:03:52 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/05 11:59:47 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int n, int base)
{
	int		count;
	long	nb;
	char	*symbols;

	nb = n;
	count = 0;
	symbols = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (0);
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= base)
		count += ft_putnbr_base(nb / base, base);
	count += ft_putchar(symbols[nb % base]);
	return (count);
}
