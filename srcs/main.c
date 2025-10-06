/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/06 15:05:58 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//check se  a linha tá em branco pra n dar merda  no history
// verifica se a linha está em branco para não a adicionar ao histórico
static int	is_blank_line(const char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (s[i] == '\0');
}

// lê a linha de input do utilizador e mostra o prompt
char *read_line(void)
{
	char	*buf;
	char	*prompt;
	char	cwd[BUFSIZ];

	// obtém o diretório atual para mostrar no prompt
	get_cwd(cwd, sizeof(cwd));
	prompt = ft_strjoin(RED, cwd);
	if (!prompt)
		return (NULL);
	buf = ft_strjoin(prompt, " "RST""C"minishell$ "RST);
	free(prompt);
	if (!buf)
		return (NULL);
	prompt = buf;
	// lê a linha de input
	buf = readline(prompt);
	free(prompt);
	// se o readline retornar NULL (ctrl-D), sai da shell
	if (!buf)
	{
		printf(RED"exit\n"RST);
		exit(EXIT_SUCCESS);
	}
	// adiciona a linha ao histórico se não estiver em branco
	if (!is_blank_line(buf))
		add_history(buf);
	return (buf);
}

int main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*cmds;
	t_shell	shell;

	(void)ac;
	(void)av;
	// inicializa a estrutura da shell
	shell.pid = getpid();
	shell.last_exit_status = 0;
	shell.env_list = init_env(env);
	
	print_banner();
	// configura os sinais para o modo interativo
	setup_interactive_signals();
	init_shell_history();
	// loop principal da shell
	while (1)
	{
		line = read_line();
		if (!line)
			break;
		
		// faz o parsing da linha para uma lista de comandos
		cmds = parse_line(line, &shell);
		
		// se o parsing for bem sucedido, executa o pipeline
		if (cmds)
		{
			shell.last_exit_status = execute_pipeline(cmds, &shell);
			free_cmds(cmds); // liberta a memória da lista de comandos
		}
		
		free(line); // liberta a memória da linha lida
	}
	
	save_shell_history();
	return (shell.last_exit_status);
}


//facilitar

// ls -l | hvxjvjl | echo "|ola"

//ls/2-l/2\3\2echo\2" OLA SOU O HENRIQUE"

//FAZER UM SPLIT SUPER CHIQUE 
//flags de in_aspas e in_nao  me lembro

//linked lists

//definir variaveis de environment com export e ler com echo

//handle sinais aqui (SIGINT CTRL D, CTRL C, CTRL \)

//figure out o que sao env e como manda las junto com os tokens???????????

//fazer o comando export e env (EXPORT MOSTRA ENVS SEM VALOR bobao)

//descobrir como expandir variaveis (detetar dollar sign como ir buscar ao env o valor)

//Todo: descobrir se é suposto entrar em modo dquote se as aspas tiverem abertas