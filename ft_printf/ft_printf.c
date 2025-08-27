/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:09:05 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/05 12:18:23 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(char format, va_list ap)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		count += ft_putstring(va_arg(ap, char *));
	else if (format == 'd')
		count += ft_putnbr_base(va_arg(ap, int), 10);
	else if (format == 'i')
		count += ft_putnbr_base(va_arg(ap, int), 10);
	else if (format == 'x')
		count += ft_putnbr_basex(va_arg(ap, unsigned int), 16, 0);
	else if (format == 'X')
		count += ft_putnbr_basex(va_arg(ap, unsigned int), 16, 1);
	else if (format == '%')
		count += ft_putchar('%');
	else if (format == 'p')
		count += ft_putpointer(va_arg(ap, void *));
	else if (format == 'u')
		count += ft_putnbr_unsigned(va_arg(ap, unsigned int), 10);
	return (count);
}

int	ft_printf(const char	*string,	...)
{
	va_list	ap;
	int		count;
	int		i;

	va_start(ap, string);
	i = 0;
	count = 0;
	if (!string || (string[0] == '%' && string[1] == '\0')
		|| write(1, 0, 0) == -1)
		return (-1);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			count += print_format(string[i + 1], ap);
			i++;
		}
		else
			count += ft_putchar(string[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
