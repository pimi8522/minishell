/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/17 14:41:45 by adores & mi      ###   ########.fr       */
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
	char	**args;
	int		i;
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env(env);
	print_banner();
//sinais de lixo
	signal(SIGINT, sigint_handler);  /* Ctrl+C */
	signal(SIGQUIT, SIG_IGN);        /* Ctrl+backslash */
	init_shell_history();

	while (1)
	{
		line = read_line();
		if (!line)
			break;
			
		args = shell_split(line);
		i = 0;
		while (args && args[i])
		{
			printf("You entered: %s\n", args[i]);
			i++;
		}
		shell_launch(args, env_list);
		i = 0;
		while (args && args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		free(line);
	}
	
 // guardar history aqui
	save_shell_history();
	return (EXIT_SUCCESS);
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