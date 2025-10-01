/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/01 12:26:21 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//check se  a linha tá em branco pra n dar merda  no history
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

//dá display ao current directory, junto de adicionar a linha à history se n for em branco
char *read_line(void)
{
	char	*buf;
	char	*prompt;
	char	cwd[BUFSIZ];

	get_cwd(cwd, sizeof(cwd));
	prompt = ft_strjoin(RED, cwd);
	if (!prompt)
		return (NULL);
	buf = ft_strjoin(prompt, " "RST""C"minishell$ "RST);
	free(prompt);
	if (!buf)
		return (NULL);
	prompt = buf;
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		printf(RED"exit\n"RST);
		exit(EXIT_SUCCESS);
	}
//history type shit
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
	shell.pid = getpid();
	shell.last_exit_status = 0;
	shell.env_list = init_env(env);
	
	print_banner();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell_history();
	while (1)
	{
		line = read_line();
		if (!line)
			break;
		
		// Use the new parser to create a structured command list
		cmds = parse_line(line);
		
		// If parsing was successful, pass the list to the new execution engine
		if (cmds)
		{
			shell.last_exit_status = execute_pipeline(cmds, &shell);
			free_cmds(cmds); // Free the allocated command list
		}
		
		free(line); // Free the line read from input
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