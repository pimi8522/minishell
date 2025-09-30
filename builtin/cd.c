/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/30 16:05:41 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_env **env_list)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		set_env_var(env_list, "OLDPWD", get_env_value(*env_list, "PWD"));
		set_env_var(env_list, "PWD", cwd);
	}
}

void	ft_cd(char **args, t_env **env_list)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value(*env_list, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
		perror("minishell: cd");
	else
		update_pwd(env_list);
}

