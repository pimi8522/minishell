/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:00:49 by adores            #+#    #+#             */
/*   Updated: 2025/04/16 16:59:18 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = content;
	node -> next = NULL;
	return (node);
}
/* #include <stdio.h>

int main(void)
{
	t_list *node;
	char *str = "Hello world";
	node = ft_lstnew(str);
	if (node)
	{
		printf("Content: %s\n", (char *)node->content);
		if (node -> next == NULL)
			printf("Next node is null");
	}
	else
		printf("Error");
	return (0);
} */