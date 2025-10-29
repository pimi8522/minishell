/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:53:15 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/29 16:35:04 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_shell *shell)
{
	char	*cwd;

	shell->last_exit_status = 0;
	cwd = getcwd(NULL, 0); //se o buffer for null ele aloca um array com o tamanho necessário
	if (cwd == NULL)
	{
		cwd = get_env_value(shell, "PWD");
		if (cwd == NULL)
		{
			ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			shell->last_exit_status = 1;
			return ;
		}
		else
			printf("%s\n", cwd);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}

/*se tiver argumentos dá erro*/