/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/14 16:59:53 by adores & mi      ###   ########.fr       */
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
		if(!original_path)
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

void	ft_cd(char **args, t_shell *shell)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	// guarda o diretório de trabalho atual (pwd)
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: error retrieving current directory");
		shell->last_exit_status = 1;
		return ;
	}
	path = get_target_path(args, shell);
	// se não houver argumentos, o caminho é a variável de ambiente HOME
	if (!path)
	{
		shell->last_exit_status = 1;
		return ;
	}
	// muda o diretório
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		shell->last_exit_status = 1;
	}
	else
	{
		shell->last_exit_status = 0;
		if (!find_env_node(shell->env_list, "OLDPWD"))
			set_env_var(shell, "OLDPWD", NULL);
		set_env_var(shell, "OLDPWD", old_pwd);
		if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
			set_env_var(shell, "PWD", new_pwd);
	}
	free(path);
}

