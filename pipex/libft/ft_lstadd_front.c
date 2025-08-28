/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:02:47 by adores            #+#    #+#             */
/*   Updated: 2025/04/17 17:02:05 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/* #include <stdio.h>

int main(void)
{
	t_list *head = NULL;
	t_list *node1 = ft_lstnew("primeiro");
	ft_lstadd_front(&head, node1);
	printf("Res: %s\n", (char *)head->content);
} */