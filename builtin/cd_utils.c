/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:17:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/30 11:56:31 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_home(t_shell *shell)
{
	char	*home;
	
	home = get_env_value(shell, "HOME");
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	return(home);
}

static char	*cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_value(shell, "OLDPWD");
	if(!oldpwd || !*oldpwd)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

char	*get_target_path(char **args, t_shell *shell)
{
	if (!args[1])
		return(cd_home(shell));
	if (ft_strcmp(args[1], "-") == 0)
		return(cd_oldpwd(shell));
	return (args[1]);
}
