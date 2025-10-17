/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/17 14:57:00 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

