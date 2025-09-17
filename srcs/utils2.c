/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:19:53 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/17 15:15:09 by adores & mi      ###   ########.fr       */
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

static int	count_env_nodes(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	**convert_env_to_array(t_env *env_list)
{
	char	**env_array;
	char	*temp;
	int		count;
	int		i;

	count = count_env_nodes(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if(!env_array)
		return(NULL);
	i = 0;
	while(env_list)
	{
		temp = ft_strjoin(env_list->key, "=");
		env_array[i] = ft_strjoin(temp, env_list->value);
		free(temp);
		env_list = env_list->next;
		i++;
	}
	env_array[i] = NULL;
	return(env_array);
}