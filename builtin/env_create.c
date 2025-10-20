/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:24:55 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/20 11:24:55 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if(!new_node)
		return(NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void add_env_var(t_env **head, t_env **current, char *env)
{
	char 	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return ;
	key = ft_substr(env, 0, equal_sign - env);
	value = ft_strdup(equal_sign + 1);
	if (!*head)
	{
		*head = new_env_node(key, value);
		*current = *head;
	}
	else
	{
		(*current)->next = new_env_node(key, value);
		*current = (*current)->next;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	head = NULL;
	current = NULL;
	i = -1;
	while(envp[++i])
		add_env_var(&head, &current, envp[i]);
	return (head);
}


void	add_env_node_back(t_env **env_list_head, t_env *new_node)
{
	t_env	*current;

	if(!*env_list_head)
	{
		*env_list_head = new_node;
		return;
	}
	current = *env_list_head;
	while(current->next)
		current = current->next;
	current->next = new_node;
}

void	free_env_node(t_env *node)
{
	if(!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
