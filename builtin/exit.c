/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:54:56 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/02 10:15:50 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	size_t	i;

	if (!s || !s[0])
		return(0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if(!s[i])
		return (0);
	while(s[i])
	{
		if(!ft_isdigit(s[i]))
			return(0);
		i++;
	}
	return(1);
}

void	exit_builtin(char **args, t_shell *shell)
{
	int	exit_code;

	if(!args[1])
		exit(shell->last_exit_status);
	if(!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if(args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	exit_code = ft_atoi(args[1]);
	exit((unsigned char)exit_code);
}
