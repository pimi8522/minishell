/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/06 16:04:00 by adores & mi      ###   ########.fr       */
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
		return;
	}
	// se não houver argumentos, o caminho é a variável de ambiente HOME
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
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(shell, "OLDPWD");
		if (!path)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			shell->last_exit_status = 1;
			return ;
		}
		printf("%s\n", path);
	}
	else
		// senão, o caminho é o primeiro argumento
		path = args[1];
	// muda o diretório
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		shell->last_exit_status = 1;
		return ;
	}
	// obtém o novo diretório de trabalho
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("cd: error retrieving new directory");
		shell->last_exit_status = 1;
		return;
	}
	// atualiza as variáveis de ambiente OLDPWD e PWD
	set_env_var(shell, "OLDPWD", old_pwd);
	set_env_var(shell, "PWD", new_pwd);
	shell->last_exit_status = 0;
}

