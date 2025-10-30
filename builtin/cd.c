/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/30 15:17:21 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_shell *shell, char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	write(2, ": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	shell->last_exit_status = 1;
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*old_pwd;
	char	*path;

	if (args[1] && args[2])
	{
		shell->last_exit_status = 1;
		return(ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	}
	old_pwd = get_env_value(shell, "PWD");
	path = get_target_path(args, shell);
	if (!path)
		return (shell->last_exit_status = 1, 1);
	if (chdir(path) != 0)
		return(cd_error(shell, path), 1);
	else
	{
		set_env_var(shell, "OLDPWD", old_pwd);
		if (getcwd(old_pwd, sizeof(old_pwd)) != NULL)
			set_env_var(shell, "PWD", old_pwd);
		else
			set_env_var(shell, "PWD", "");
		shell->last_exit_status = 0;
	}
	return (0);
}

//mudar para int
// se tiver mais que 1 argumento tem de dar erro
