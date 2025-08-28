/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:03:13 by adores            #+#    #+#             */
/*   Updated: 2025/04/22 14:15:26 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst-> next;
	return (lst);
}
/* #include <stdio.h>
int main(void)
{
	t_list *head = NULL;
	t_list *node1 = ft_lstnew("ANA");
	t_list *node2 = ft_lstnew("RITA");
	
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	
	t_list *last = ft_lstlast(head);
	printf("ULTIMO = %s\n", (char *)last->content);
	return(0);
} */