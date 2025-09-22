/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:50:49 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/22 10:52:02 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

