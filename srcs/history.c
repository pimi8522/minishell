/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/03 17:14:46 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comandos ficam guardados em minishell.history
int	init_shell_history(void)
{
	char	*home;
	char	*history_path;
	int		ret;

	home = getenv("HOME");
	if (!home)
		return (-1);
	history_path = ft_strjoin(home, "/.minishell_history");
	if (!history_path)
		return (-1);
	ret = read_history(history_path); //CANT USE ESTA FUNCAO CHANGE LATER (so ta ca pra semana do skong porque ja n tenho paciencia)
	free(history_path);
	return (ret);
}

//guardar no actual ficheiro
void	save_shell_history(void)
{
	char	*home;
	char	*history_path;

	home = getenv("HOME");
	if (!home)
		return ;
	history_path = ft_strjoin(home, "/.minishell_history");
	if (!history_path)
		return ;
	write_history(history_path); //CANT USE ESTA FUNCAO CHANGE LATER (so ta ca pra semana do skong porque ja n tenho paciencia)
	free(history_path);
}
