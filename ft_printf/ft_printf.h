/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:09:24 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/09 11:27:57 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *string, ...);
int	ft_putchar(int chr);
int	ft_putstring(char *s);
int	ft_putnbr_base(int n, int base);
int	ft_putnbr_unsigned(uintptr_t nb, int base);
int	ft_putpointer(void *ptr);
int	ft_putnbr_basex(unsigned int n, int base, int caps);
int	ft_putaddr(uintptr_t addr, int base);

#endif