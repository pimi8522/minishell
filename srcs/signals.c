/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:08 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/01 18:46:00 by Roo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler para SIGINT (ctrl-C) no modo interativo
// mostra um novo prompt numa nova linha
void	interactive_sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// handler para SIGINT (ctrl-C) durante a execução de um comando
// imprime uma nova linha para manter o output limpo
void	exec_sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}

// handler para SIGQUIT (ctrl-\) durante a execução de um comando
// imprime a mensagem "Quit"
void	exec_sigquit_handler(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	exit(130);
}

// configura os handlers de sinal para o modo interativo
void	setup_interactive_signals(void)
{
	signal(SIGINT, interactive_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// configura os handlers de sinal para o modo de execução
void	setup_exec_signals(void)
{
	signal(SIGINT, exec_sigint_handler);
	signal(SIGQUIT, exec_sigquit_handler);
}
