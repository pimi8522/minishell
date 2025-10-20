/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/20 14:46:32 by miduarte &       ###   ########.fr       */
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
static char	*create_prompt(void)
{
	char	*prompt_part;
	char	*full_prompt;
	char	cwd[BUFSIZ];

	get_cwd(cwd, sizeof(cwd));
	prompt_part = ft_strjoin(RED, cwd);
	if (!prompt_part)
		return (NULL);
	full_prompt = ft_strjoin(prompt_part, " "RST""C"minishell$ "RST);
	free(prompt_part);
	return (full_prompt);
}

char	*read_line(t_shell *shell)
{
	char	*buf;
	char	*prompt;

	prompt = create_prompt();
	if (!prompt)
		return (NULL);
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		printf(RED"exit\n"RST);
		exit(shell->last_exit_status);
	}
	if (!is_blank_line(buf))
		add_history(buf);
	return (buf);
}

static void	run_shell(t_shell *shell)
{
	char	*line;
	t_cmd	*cmds;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = read_line(shell);
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		cmds = parse_line(line, shell);
		if (cmds)
		{
			shell->last_exit_status = execute_pipeline(cmds, shell);
			free_cmds(cmds);
		}
		else
			shell->last_exit_status = 2;
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.pid = getpid();
	shell.last_exit_status = 0;
	shell.env_list = init_env(env);
	if (!find_env_node(shell.env_list, "OLDPWD"))
		set_env_var(&shell, "OLDPWD", NULL);
	if (isatty(STDIN_FILENO))
	{
		print_banner();
		setup_interactive_signals();
		init_shell_history();
	}
	run_shell(&shell);
	if (isatty(STDIN_FILENO))
		save_shell_history();
	return (shell.last_exit_status);
}
