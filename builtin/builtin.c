/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/30 16:05:17 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_builtin2(char **args, t_env **env_list)
{
	if(ft_strcmp(args[0], "echo") == 0)
	{
		echo_builtin(args);
		return(1);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(args, env_list);
		return (1) ;
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		pwd_builtin();
		return(1);
	}
	return(0);
}

int	exe_builtin(char **args, t_env **env_list)
{
	if(!args || !args[0])
		return(0);
	if(exe_builtin2(args, env_list))
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		exit_builtin(args);
		return(1);
	}
	else if(ft_strcmp(args[0], "env") == 0)
	{
		env_builtin(*env_list);
		return(1);
	}
	else if(ft_strcmp(args[0], "unset") == 0)
	{
		unset_builtin(args, env_list);
		return(1);
	}
	else if(ft_strcmp(args[0], "export") == 0)
	{
		export_builtin(args, env_list);
		return(1);
	}
	return(0);
}
