/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:26:41 by adores            #+#    #+#             */
/*   Updated: 2025/04/21 10:09:28 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last -> next)
	{
		last = last -> next;
	}
	last -> next = new;
}
/* #include <stdio.h>
int main(void)
{
	t_list *head = ft_lstnew("first");
	t_list *nd1 = ft_lstnew("Second");
	ft_lstadd_back(&head, nd1);
	printf("%s\n", (char *)head->next->content);
} */