/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:59:57 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/30 16:06:56 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(t_env *env_list)
{
	char	**env_array;
	int		i;
	char	*equal_sign;
	char	*key;

	env_array = convert_env_to_array(env_list);
	if (!env_array)
		return;
	bubble_sort_array(env_array);
	i = 0;
	while(env_array[i])
	{
		equal_sign = ft_strchr(env_array[i], '=');
		if (equal_sign)
		{
			key = ft_substr(env_array[i], 0, equal_sign - env_array[i]);
			if (key)
			{
				printf("declare -x %s=\"%s\"\n", key, equal_sign + 1);
				free(key);
			}
		}
		else
			printf("declare -x %s\n", env_array[i]);
		i++;
	}
	free_str(env_array);
}

void	export_builtin(char **args, t_env **env_list_head)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*existing_node;
	t_env	*new_node;

	i = 1;
	if (!args[i])
	{
		print_sorted_env(*env_list_head);
		return ;
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			if(!key)
				break;
			value = ft_strdup(equal_sign + 1);
			if(!value)
			{
				free(key);
				break;
			}
			existing_node = find_env_node(*env_list_head, key);
			if(existing_node)
			{
				free(existing_node->value);
				existing_node->value = value;
				free(key);
			}
			else
			{
				new_node = new_env_node(key, value);
				if (!new_node)
				{
					free(key);
					free(value);
					break;
				}
				add_env_node_back(env_list_head, new_node);
			}
		}
		i++;
	}
}
