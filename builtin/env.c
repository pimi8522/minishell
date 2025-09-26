/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:56:31 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/26 16:32:25 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value && (ft_strcmp(current->key, "?") != 0))
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
