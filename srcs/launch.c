/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:39:56 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/30 15:20:52 by adores & mi      ###   ########.fr       */
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
	if (!exe_builtin(cmd->flag, shell))
		exit(shell->last_exit_status);
	// senão, executa o comando externo
	execute_command(cmd->flag, env_array);
	exit(EXIT_FAILURE);
}

int execute_single_builtin(t_cmd *cmd, t_shell *shell)
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
