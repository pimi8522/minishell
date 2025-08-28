/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:35:37 by adores            #+#    #+#             */
/*   Updated: 2025/04/17 16:58:49 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* #include <stdio.h>
void to_upper(unsigned int i, char *c)
{
	(void)i; // ignoramos o índice aqui
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}
int main(void)
{
	char str[] = "hello world";
	ft_striteri(str, &to_upper);
	printf("Resultado: %s\n", str);
    return 0;
} */