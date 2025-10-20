/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:53:18 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/20 13:53:18 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_all_variables(t_cmd *cmds, t_shell *shell)
{
	t_cmd *tmp;

	tmp = cmds;
	while (tmp)
	{
		expand_variables(tmp, shell);
		tmp = tmp->next;
	}
}

static int	handle_single_builtin(t_cmd *cmds, t_shell *shell)
{
	if (!cmds->next && is_builtin(cmds->flag))
		return (execute_single_builtin(cmds, shell));
	return (0);
}

static int	create_and_fork_process(t_cmd *cmd, t_shell *shell, int *input_fd, pid_t *last_pid)
{
	int		pipe_fds[2];

	if(cmd->next && pipe(pipe_fds) == -1)
		return (perror("minishell: pipe"), 1);
	// cria um processo filho
	*last_pid = fork();
	if (*last_pid == -1)
		return (perror("minishell: fork"), 1);
	// no processo filho, chama a função execute_child
	if(*last_pid == 0)
		execute_child(cmd, shell, *input_fd, pipe_fds);
	// no processo pai, fecha os descritores apropriados
	if(cmd->next)
		close(pipe_fds[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	// o input do próximo comando será o output do pipe atual
	if (cmd->next)
		*input_fd = pipe_fds[0];
	return (0);
}

static int	wait_for_children(pid_t last_pid)
{
	int	status;

	status = 0;
	if(last_pid != -1)
		waitpid(last_pid, &status, 0);
	// espera por todos os outros processos filhos
	while (wait(NULL) > 0);
	// restaura os sinais para o modo interativo
	setup_interactive_signals();
	// retorna o status de saída do último comando
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (127);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	pid_t	last_pid;
	int		input_fd;

	if (!cmds)
		return (0);
	// primeiro, expande as variáveis para todos os comandos
	expand_all_variables(cmds, shell);
	// se for um único comando e for um builtin, executa diretamente
	if(handle_single_builtin(cmds, shell))
		return (0);
	// configura os sinais para o modo de execução
	setup_exec_signals();
	last_pid = -1;
	input_fd = STDIN_FILENO;
	// itera sobre a lista de comandos
	while(cmds)
	{
		if (create_and_fork_process(cmds, shell, &input_fd, &last_pid))
		cmds = cmds->next;
	}
	return (wait_for_children(last_pid));
}
