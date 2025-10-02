/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:58:22 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/02 10:33:17 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(char **args, t_shell *shell)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	shell->last_exit_status = 0;
	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if(!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit_status = 1;
		}
		else
		{
			current = shell->env_list;
			prev = NULL;
			while(current)
			{
				if(ft_strcmp(current->key, args[i]) == 0)
				{
					if (prev == NULL)
						shell->env_list = current->next;
					else
						prev->next = current->next;
					free_env_node(current);
					break;
				}
				prev = current;
				current = current->next;
			}
		}
		i++;
	}
}
