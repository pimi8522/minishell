/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/01 16:00:59 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_cd(char **args, t_shell *shell)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: error retrieving current directory");
		shell->last_exit_status = 1;
		return;
	}
	if (!args[1])
	{
		path = get_env_value(shell, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			shell->last_exit_status = 1;
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		shell->last_exit_status = 1;
		return;
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("cd: error retrieving new directory");
		shell->last_exit_status = 1;
		return;
	}
	set_env_var(shell, "OLDPWD", old_pwd);
	set_env_var(shell, "PWD", new_pwd);
	shell->last_exit_status = 0;
}

