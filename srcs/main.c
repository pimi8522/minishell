/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:19:30 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/29 17:35:00 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line(void)
{
	char	*buf;
	size_t	bufsize;
	char	cwd[BUFSIZ];

	buf = NULL;
	get_cwd(cwd, sizeof(cwd));
	printf(RED"%s "RST, cwd);
	printf(""C"minishell$ "RST);
	if (getline(&buf, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			printf(RED"EOF\n"RST);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror(RED"readline"RST);
			exit(EXIT_FAILURE);
		}
	}
	return (buf);
}

int main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	print_banner();

	while ((line = read_line()))
	{
		args = shell_split(line);
		i = 0;
		while (args && args[i])
		{
			printf("You entered: %s\n", args[i]);
			i++;
		}
		shell_launch(args, env);
		i = 0;
		while (args && args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		free(line);
	}
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