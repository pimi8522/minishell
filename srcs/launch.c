/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:39:56 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/09 15:47:03 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// esta função é executada no processo filho
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2])
{
	char	**env_array;

	// o processo filho deve ter o comportamento padrão para os sinais
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// redireciona o input, se necessário
	if (cmd->in != STDIN_FILENO)
	{
		if (dup2(cmd->in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->in);
	}
	else if(input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	// redireciona o output, se necessário
	if(cmd->out != STDOUT_FILENO)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->out);
	}
	// se houver um próximo comando, o output é o pipe
	else if(cmd->next)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
	}
	// fecha os descritores do pipe no filho
	if (cmd->next)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	env_array = convert_env_to_array(shell->env_list);
	// se for um builtin, executa e sai
	if (exe_builtin(cmd->flag, shell))
		exit(shell->last_exit_status);
	// senão, executa o comando externo
	execute_command(cmd->flag, env_array);
	exit(EXIT_FAILURE);
}

static int execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);

	if (cmd->in != STDIN_FILENO)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != STDOUT_FILENO)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	exe_builtin(cmd->flag, shell);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (shell->last_exit_status);
}


// função principal para executar um ou mais comandos (pipeline)
int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	pid_t	last_pid;
	int		status;
	t_cmd	*current_cmd;
	int		pipe_fds[2];
	int		input_fd;

	if (!cmds)
		return (0);
	// primeiro, expande as variáveis para todos os comandos
	current_cmd = cmds;
	while (current_cmd)
	{
		expand_variables(current_cmd, shell);
		current_cmd = current_cmd->next;
	}
	// se for um único comando e for um builtin, executa diretamente
	if (!cmds->next && is_builtin(cmds->flag))
	{
		return (execute_single_builtin(cmds, shell));
	}
	// configura os sinais para o modo de execução
	setup_exec_signals();
	last_pid = -1;
	status = 0;
	current_cmd = cmds;
	input_fd = STDIN_FILENO;
	// itera sobre a lista de comandos
	while(current_cmd)
	{
		// se houver um próximo comando, cria um pipe
		if(current_cmd->next)
		{
			if(pipe(pipe_fds) == -1)
			{
				perror("minishell: pipe");
				return (1);
			}
		}
		// cria um processo filho
		last_pid = fork();
		if (last_pid == -1)
		{
			perror("minishell: fork");
			return (1);
		}
		// no processo filho, chama a função execute_child
		if(last_pid == 0)
			execute_child(current_cmd, shell, input_fd, pipe_fds);
		// no processo pai, fecha os descritores apropriados
		if(current_cmd->next)
			close(pipe_fds[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		// o input do próximo comando será o output do pipe atual
		if (current_cmd->next)
			input_fd = pipe_fds[0];
		current_cmd = current_cmd->next;
	}
	// espera pelo último processo filho
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
