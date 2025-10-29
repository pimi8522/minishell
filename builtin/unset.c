/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:58:22 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/29 15:48:12 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env_list;
	prev = NULL;
	while(current)
	{
		if(ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				shell->env_list = current->next;
			else
				prev->next = current->next;
			free_env_node(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	unset_builtin(char **args, t_shell *shell)
{
	int	i;

	shell->last_exit_status = 0;
	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (get_env_value(shell, args[i]))
			remove_env_var(shell, args[i]);
		i++;
	}
}
