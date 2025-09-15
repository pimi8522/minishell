/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/15 15:41:26 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_builtin(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
			printf(" ");
		i++;
	}
	if(newline == 1)
		printf("\n");
}

void	ft_cd(char **args)
{
	if(!args[1])
	{
		write(2, "minishell: cd: missing argument\n", 31);
		return ;
	}
	if(chdir(args[1]) != 0)
		perror("minishell: cd");
}

static void pwd_builtin(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
		perror("pwd");
}

int	exe_builtin(char **args)
{
	if(!args || !args[0])
		return(0);
	if(ft_strcmp(args[0], "echo") == 0)
	{
		echo_builtin(args);
		return(1);
	}
	else if (ft_strcmp((args[0]), "cd") == 0)
	{
		ft_cd(args);
		return (1) ;
	}
	else if (ft_strcmp((args[0]), "pwd") == 0)
	{
		pwd_builtin();
		return(1);
	}
	return(0);
}