/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:54:56 by adores & mi       #+#    #+#             */
/*   Updated: 2025/11/04 14:56:47 by adores & mi      ###   ########.fr       */
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

static bool	ft_exitatoll(const char	*str, long long *exit_code)
{
	int	i;
	int	sign;
	int	digit;

	sign = 1;
	i = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i])
	{
		digit = str[i] - '0';
		if (sign == -1 && (-(*exit_code) < (LLONG_MIN + digit) / 10))
			return (false);
		if (sign == 1 && (*exit_code > (LLONG_MAX - digit) / 10))
			return (false);
		*exit_code = (*exit_code * 10) + digit;
		i++;
	}
	*exit_code *= sign;
	return (true);
}

int	exitclean(t_shell *shell, unsigned char exit_code)
{
	free_env_list(shell->env_list);
	exit(exit_code);
}

int	exit_builtin(char **args, t_shell *shell)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", 2);
	if(!args[1])
	{
		free_str_array(args);
		exitclean(shell, (unsigned char)shell->last_exit_status);
	}	
	if(!is_numeric(args[1]) || !ft_exitatoll(args[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_str_array(args);
		exitclean(shell, 2);
	}
	if(args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	free_str_array(args);
	exitclean(shell, (unsigned char)exit_code);
	return (0);
}

//falta dar free