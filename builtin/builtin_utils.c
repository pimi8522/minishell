/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:19:53 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/16 11:47:45 by adores & mi      ###   ########.fr       */
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

static char *make_env_entry(t_env *node)
{
	char 	*temp;
	char	*entry;

	if (node->value)
	{
		temp = ft_strjoin(node->key, "=");
		entry = ft_strjoin(temp, node->value);
		free(temp);
	}
	else
		entry = ft_strdup(node->key);
	return (entry);
}

char	**convert_env_to_array(t_env *env_list)
{
	char	**env_array;
	int		count;
	int		i;

	count = count_env_nodes(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if(!env_array)
		return(NULL);
	i = 0;
	while(env_list)
	{
		env_array[i++] = make_env_entry(env_list);
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return(env_array);
}

char	*get_env_value(t_shell *shell, const char *key)
{
	t_env	*node;

	// Verificação de segurança para ponteiros nulos
	if (!key || !shell)
		return (NULL);

	// Reutiliza a função find_env_node para encontrar o nó
	node = find_env_node(shell->env_list, key);
	if (node)
	{
		// Se o nó for encontrado, retorna o seu valor
		return (node->value);
	}

	// Se não for encontrado, retorna NULL
	return (NULL);
}

t_env	*find_env_node(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
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

static int	count_array_strings(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return(0);
	while (arr[count])
		count++;
	return(count);
}

void	bubble_sort_array(char **arr)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	n = count_array_strings(arr);
	if (n < 2)
		return ;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while(j < n -i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_env_node(t_env *node)
{
	if(!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

// Define ou atualiza uma variável de ambiente.
void	set_env_var(t_shell *shell, const char *key, const char *value)
{
	t_env	*env_node;

	env_node = find_env_node(shell->env_list, key);
	if (env_node)
	{
		// A variável já existe, atualiza o valor.
		free(env_node->value); // Liberta o valor antigo
		if (value)
			env_node->value = ft_strdup(value);
		else
			env_node->value = NULL;
	}
	else
	{
		// A variável não existe, cria um novo nó.
		// new_env_node now handles the duplication
		env_node = new_env_node((char *)key, (char *)value);
		if (!env_node)
			return; // Tratar erro de alocação
		add_env_node_back(&shell->env_list, env_node);
	}
}
