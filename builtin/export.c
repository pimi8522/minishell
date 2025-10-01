/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:59:57 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/01 19:51:53 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	if(!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return(0);
		str++;
	}
	return (1);
}

// imprime as variáveis de ambiente por ordem alfabética
static void	print_sorted_env(t_shell *shell)
{
	char	**env_array;
	int		i;
	char	*equal_sign;
	char	*key;

	env_array = convert_env_to_array(shell->env_list);
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
				// imprime no formato: declare -x KEY="value"
				printf("declare -x %s=\"%s\"\n", key, equal_sign + 1);
				free(key);
			}
		}
		else
			// imprime variáveis sem valor, ex: declare -x VAR
			printf("declare -x %s\n", env_array[i]);
		i++;
	}
	free_str(env_array);
}

void	export_builtin(char **args, t_shell *shell)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	shell->last_exit_status = 0;
	// se não houver argumentos, imprime as variáveis de ambiente
	if (!args[1])
	{
		print_sorted_env(shell);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if(!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit_status = 1;
		}
		else
		{
			equal_sign = ft_strchr(args[i], '=');
			if(equal_sign)
			{
				// caso: export VAR=value
				key = ft_substr(args[i], 0, equal_sign - args[i]);
				value = ft_strdup(equal_sign + 1);
				set_env_var(shell, key, value);
				free(key);
				free(value);
			}
			else
			{
				// caso: export VAR
				// adiciona a variável apenas se ela não existir, com um valor nulo
				// para evitar que `set_env_var` falhe com `strdup(NULL)`
				if(!find_env_node(shell->env_list, args[i]))
					set_env_var(shell, args[i], "");
			}
		}
		i++;
	}
}
