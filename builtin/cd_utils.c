/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:17:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/17 14:59:10 by adores & mi      ###   ########.fr       */
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
	return(ft_strdup(home));
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
	return (ft_strdup(oldpwd));
}

static char *cd_tilde(t_shell *shell, char *arg)
{
	char	*home;
	char	*path;

	home = get_env_value(shell, "HOME");
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	if (ft_strcmp(arg, "~") == 0)
		path = ft_strdup(home);
	else
		path = ft_strjoin(home, arg + 1);
	return(path);
}

char	*get_target_path(char **args, t_shell *shell)
{
	if (!args[1])
		return(cd_home(shell));
	if (ft_strcmp(args[1], "-") == 0)
		return(cd_oldpwd(shell));
	if (args[1][0] == '~')
		return(cd_tilde(shell, args[1]));
	return (ft_strdup(args[1]));
}
