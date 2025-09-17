/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:19:53 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/17 14:32:18 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if(!new_node)
		return(NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	head = NULL;
	i = 0;
	while(envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			key = ft_substr(envp[i], 0, equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
			if (!head)
			{
				head = new_env_node(key, value);
				current = head;
			}
			else
			{
				current->next = new_env_node(key, value);
				current = current->next;
			}
		}
		i++;
	}
	return (head);
}