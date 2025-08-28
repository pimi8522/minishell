/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:59:46 by adores            #+#    #+#             */
/*   Updated: 2025/04/22 14:09:28 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}
/* #include <stdio.h>

int main(void)
{
	t_list *head = NULL;
	t_list *node1 = ft_lstnew("HELLO");
	t_list *node2 = ft_lstnew("WORLD");
	
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	
	int size = ft_lstsize(head);
	printf("Tamanho da lista: %d\n", size);
	return (0);
} */