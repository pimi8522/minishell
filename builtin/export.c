/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:59:57 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/29 15:31:04 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	if(!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return(0);
		str++;
	}
	return (1);
}

static void	export_error(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->last_exit_status = 1;
}

static void	handle_export_assignment(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	set_env_var(shell, key, value);
}

static void	handle_export_no_value(t_shell *shell, char *arg)
{
	if(!find_env_node(shell->env_list, arg))
		set_env_var(shell, arg, NULL);
}

void	export_builtin(char **args, t_shell *shell)
{
	int	i;

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
			export_error(shell, args[i]);
		else if(ft_strchr(args[i], '='))
			handle_export_assignment(shell, args[i]);
		else
			handle_export_no_value(shell, args[i]);
		i++;
	}
}
