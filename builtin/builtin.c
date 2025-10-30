/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/30 16:46:02 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		return (1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	return (0);
}

int	exe_builtin(char **args, t_shell *shell)
{
	if(!args || !args[0])
		return(1);
	if(ft_strcmp(args[0], "echo") == 0)
		return(echo_builtin(args, shell));
	else if (ft_strcmp(args[0], "cd") == 0)
		return(ft_cd(args, shell));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return(pwd_builtin(shell));
	if (ft_strcmp(args[0], "exit") == 0)
		return(exit_builtin(args, shell));
	else if(ft_strcmp(args[0], "env") == 0)
		return(env_builtin(shell));
	else if(ft_strcmp(args[0], "unset") == 0)
		return(unset_builtin(args, shell));
	else if(ft_strcmp(args[0], "export") == 0)
		return(export_builtin(args, shell));
	return(1);
}
