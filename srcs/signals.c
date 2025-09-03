/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:08 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/03 17:10:39 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;  //check later
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
