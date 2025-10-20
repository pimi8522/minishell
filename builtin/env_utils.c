/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:19:53 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/20 11:33:50 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
