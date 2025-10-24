/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/24 15:13:24 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_shell *shell, char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	shell->last_exit_status = 1;
}

void	ft_cd(char **args, t_shell *shell)
{
	char	old_pwd[PATH_MAX];
	char	*path;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: error retrieving current directory");
		shell->last_exit_status = 1;
		return ;
	}
	path = get_target_path(args, shell);
	if (!path)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (chdir(path) != 0)
	{
		cd_error(shell, path);
	}
	else
	{
		set_env_var(shell, "OLDPWD", old_pwd);
		if (getcwd(old_pwd, sizeof(old_pwd)) != NULL)
			set_env_var(shell, "PWD", old_pwd);
		else
			set_env_var(shell, "PWD", "");
		shell->last_exit_status = 0;
	}
	free(path);
}

