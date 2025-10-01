/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:39:56 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/01 19:54:06 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void execute_single_command(char **args, t_env *env_list)
{
	pid_t	pid;
	int		status;
	char	**env_array;

	pid = fork();
	if (pid == 0)
	{
		printf("Execute single command: %s...\n", args[0]);
		env_array = convert_env_to_array(env_list);
		execute_command(args, env_array);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell: fork error");
	else
	{
		waitpid(pid, &status, 0);
	}
}

static void execute_pipe_command(char **cmd1, char **cmd2, t_env *env_list)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
	char	**env_array;

	printf("Executing pipe command: %s | %s..\n", cmd1[0], cmd2[0]);
	if(pipe(fd) == -1)
	{
		perror("minishell: pipe error");
		return;
	}
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		env_array = convert_env_to_array(env_list);
		execute_command(cmd1, env_array);
	}
	pid2 = fork();
	if(pid2 < 0)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		env_array = convert_env_to_array(env_list);
		execute_command(cmd2, env_array);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
}

static int	find_pipe_index(char **args)
{
	int i;
	i = 0;
	while(args && args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return(i);
		i++;
	}
	return(-1);
}

void	shell_launch(char **args, t_env **env_list_head)
{
	int pipe_index;
	char **cmd1;
	char **cmd2;
	if(!args || !args[0])
	{
		//exit?
		return ;
	}
	if(exe_builtin(args, env_list_head))
		return;
	pipe_index = find_pipe_index(args);
	if (pipe_index != -1)
	{
		args[pipe_index] = NULL;
		cmd1 = args;
		cmd2 = &args[pipe_index + 1];
		if (!cmd2[0])
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			return ;
		}
		execute_pipe_command(cmd1, cmd2, *env_list_head);
	}
	else
		execute_single_command(args, *env_list_head);
}*/

// esta função é executada no processo filho
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2])
{
	char	**env_array;

	// o processo filho deve ter o comportamento padrão para os sinais
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// redireciona o input, se necessário
	if(cmd->in != STDIN_FILENO)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	else if(input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	// redireciona o output, se necessário
	if(cmd->out != STDOUT_FILENO)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	// se houver um próximo comando, o output é o pipe
	else if(cmd->next)
		dup2(pipe_fds[1], STDOUT_FILENO);
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
	if (!cmds->next && exe_builtin(cmds->flag, shell))
	{
		return (shell->last_exit_status);
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
