/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:54:56 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/22 10:55:31 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(char **args)
{
	int	exit_code;

	if(!args[1])
		exit(0);
	exit_code = ft_atoi(args[1]);
	if(args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ; // We should set a specific error status here, but for now, just return.
	}
	exit(exit_code);
}
