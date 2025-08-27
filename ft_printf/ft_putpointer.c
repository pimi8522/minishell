/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:52:39 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/09 11:28:06 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstring("(nil)"));
	count += ft_putstring("0x");
	count += ft_putaddr((uintptr_t)ptr, 16);
	return (count);
}
int	ft_putaddr(uintptr_t addr, int base)
{
	int			count;
	const char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (addr >= (uintptr_t)base)
		count += ft_putaddr(addr / base, base);
	count += ft_putchar(symbols[addr % base]);
	return (count);
}
