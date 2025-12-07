/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/21 16:33:10 by miduarte         ###   ########.fr       */
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
	char	 cwd[PATH_MAX];
	/* Increase buffer to silence -Wformat-truncation while keeping stack allocation */
	char	 prompt_buf[(PATH_MAX * 2) + 256];
	size_t	 len;
	char	*line;

	get_cwd(cwd, sizeof(cwd));
	/* Build prompt safely without triggering format-truncation warning */
	len = 0;
	ft_strlcpy(prompt_buf, RED, sizeof(prompt_buf));
	len = ft_strlcat(prompt_buf, cwd, sizeof(prompt_buf));
	len = ft_strlcat(prompt_buf, " "RST, sizeof(prompt_buf));
	len = ft_strlcat(prompt_buf, C, sizeof(prompt_buf));
	len = ft_strlcat(prompt_buf, "minishell$ "RST, sizeof(prompt_buf));
	(void)len;
	line = readline(prompt_buf);
	if (!line)
	{
		printf(RED"exit\n"RST);
		exit(EXIT_SUCCESS);
	}
	if (!is_blank_line(line))
		add_history(line);
	return (line);
}

static char	*get_redir_type_str(t_token_type type)
{
	if (type == T_LESS)
		return ("< (T_LESS)");
	if (type == T_GREAT)
		return ("> (T_GREAT)");
	if (type == T_DLESS)
		return ("<< (T_DLESS)");
	if (type == T_DGREAT)
		return (">> (T_DGREAT)");
	return ("UNKNOWN");
}

/* New helpers for t_input output */
static const char	*mode_str(t_token m)
{
	if (m == REDIN)
		return "<";
	if (m == REDOUT)
		return ">";
	if (m == HDOC)
		return "<<";
	if (m == APPEND)
		return ">>";
	return "?";
}

static void	print_input_segments(t_input *list)
{
	int		idx;
	int		i;

	idx = 1;
	while (list)
	{
		printf("--- Segment %d ---\n", idx++);
		/* argv */
		printf("Args:\n");
		i = 0;
		if (list->argv)
		{
			while (list->argv[i])
			{
				printf("  argv[%d]: %s\n", i, list->argv[i]);
				i++;
			}
		}
		if (i == 0)
			printf("  (none)\n");
		/* infiles */
		printf("Infiles:\n");
		i = 0;
		if (list->infiles)
		{
			while (list->infiles[i].filename)
			{
				printf("  %s %s%s%s (quoted=%d)\n",
					mode_str(list->infiles[i].mode),
					list->infiles[i].quoted ? "\"" : "",
					list->infiles[i].filename,
					list->infiles[i].quoted ? "\"" : "",
					list->infiles[i].quoted);
				i++;
			}
		}
		if (i == 0)
			printf("  (none)\n");
		/* outfiles */
		printf("Outfiles:\n");
		i = 0;
		if (list->outfiles)
		{
			while (list->outfiles[i].filename)
			{
				printf("  %s %s%s%s (quoted=%d)\n",
					mode_str(list->outfiles[i].mode),
					list->outfiles[i].quoted ? "\"" : "",
					list->outfiles[i].filename,
					list->outfiles[i].quoted ? "\"" : "",
					list->outfiles[i].quoted);
				i++;
			}
		}
		if (i == 0)
			printf("  (none)\n");
		printf("-------------------\n");
		list = list->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*current_cmd;
	t_list	*redir_list;
	t_redir	*redir;
	int		i;
	int		j;

	current_cmd = cmds;
	i = 1;
	while (current_cmd)
	{
		printf("--- Command %d ---\n", i++);
		printf("Cmd: %s\n", current_cmd->cmd);
		printf("Args:\n");
		j = 0;
		if (current_cmd->flag)
		{
			while (current_cmd->flag[j])
			{
				printf("  arg[%d]: %s\n", j, current_cmd->flag[j]);
				j++;
			}
		}
		printf("Redirections:\n");
		redir_list = current_cmd->redirs;
		if (!redir_list)
			printf("  (none)\n");
		while (redir_list)
		{
			redir = (t_redir *)redir_list->content;
			printf("  - Type: %s, File: %s\n", \
					get_redir_type_str(redir->type), redir->file);
			redir_list = redir_list->next;
		}
		printf("-------------------\n");
		current_cmd = current_cmd->next;
	}
}

int main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*cmds;
	t_input	*inputs;
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	// inicializa a estrutura da shell
	shell.last_exit_status = 0;
	// shell.env_list = init_env(env); // separação do pars4re
	shell.env_list = NULL;
	if (isatty(STDIN_FILENO))
	{
		//print_banner();
		// configura os sinais para o modo interativo
		// setup_interactive_signals(); // separação do pars4er
	}
	// loop principal da shell
	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = read_line();
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			// free_env_list(shell.env_list);
			break;
		}
		
		/* New input parser producing t_input pipeline list */
		inputs = parser_input(line, &shell);
		if (inputs)
		{
			printf("\n--- Input Parser Output ---\n");
			print_input_segments(inputs);
			free_input_list(inputs);
		}
		else
		{
			/* fallback to old parser for debugging if needed */
			cmds = parser(line, &shell);
			if (cmds)
			{
				printf("\n--- (Legacy) Parser Output ---\n");
				print_cmds(cmds);
				free_cmds(cmds);
			}
			else
				printf("Parser retornou NULL\n");
		}
		
		free(line); // liberta a memória da linha lida
	}
	if (isatty(STDIN_FILENO))
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