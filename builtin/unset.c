/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:58:22 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/22 10:59:17 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(char **args, t_env **env_list_head)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		current = *env_list_head;
		prev = NULL;
		while(current)
		{
			if(ft_strcmp(current->key, args[i]) == 0)
			{
				if (prev == NULL)
					*env_list_head = current->next;
				else
					prev->next = current->next;
				free_env_node(current);
				break;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}
