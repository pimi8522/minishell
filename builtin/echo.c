/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:48:54 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/06 14:28:41 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
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
}
