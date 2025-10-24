/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:56:31 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/24 15:04:15 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(char *entry)
{
	char	*equal_sign;
	char	*key;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign)
	{
		key = ft_substr(entry, 0, equal_sign - entry);
		if (key)
		{
			// imprime no formato: declare -x KEY="value"
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal_sign + 1, 1);
			ft_putstr_fd("\"\n", 1);
			free(key);
		}
	}
	else
	{
		// imprime variáveis sem valor, ex: declare -x VAR
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(entry, 1);
		ft_putstr_fd("\n", 1);
	}
}

static void	print_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		if (ft_strncmp(env_array[i], "_=", 2) != 0)
			print_env_var(env_array[i]);
		i++;
	}
}

// imprime as variáveis de ambiente por ordem alfabética
void	print_sorted_env(t_shell *shell)
{
	char	**env_array;

	env_array = convert_env_to_array(shell->env_list);
	if (!env_array)
		return;
	bubble_sort_array(env_array);
	print_env_array(env_array);
	free_str(env_array);
}

void	env_builtin(t_shell *shell)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	shell->last_exit_status = 0;
}
