/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:17:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/17 14:19:03 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_path(char **args, t_shell *shell)
{
	char	*path;
	char	*home;
	char	*original_path;

	if (!args[1])
	{
		original_path = get_env_value(shell, "HOME");
		if (!original_path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return(ft_strdup(original_path));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		original_path = get_env_value(shell, "OLDPWD");
		if(!original_path || !*original_path)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return (NULL);
		}
		printf("%s\n", original_path);
		return (ft_strdup(original_path));
	}
	if (args[1][0] == '~')
	{
		home = get_env_value(shell, "HOME");
		if (!home)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		if (ft_strcmp(args[1], "~") == 0)
			path = ft_strdup(home);
		else
			path = ft_strjoin(home, args[1] + 1);
		return(path);
	}
	return (ft_strdup(args[1]));
}