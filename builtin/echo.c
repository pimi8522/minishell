/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:48:54 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/30 14:42:46 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while(arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

int	echo_builtin(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		ft_putstr_fd(args[i], 1);
		if(args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if(newline == 1)
		ft_putstr_fd("\n", 1);
	shell->last_exit_status = 0;
	return (0);
}
