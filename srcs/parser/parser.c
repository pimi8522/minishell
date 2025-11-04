/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte & adores@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:03 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/04 11:03:19 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// verifica se um caractere é um metacaractere (|, <, >)
static int	is_meta_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	handle_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
	else if (c == '"' && !*in_squote)
		*in_dquote = !*in_dquote;
}

static int	is_token_char(char c, int in_s, int in_d)
{
	if (in_s || in_d)
		return (1);
	if (!ft_strchr(WHITESPACE, c) && !is_meta_char(c))
		return (1);
	return (0);
}

static void	process_token(const char *s, size_t *i, int *in_s, int *in_d)
{
	if (is_meta_char(s[*i]))
	{
		if ((s[*i] == '<' && s[*i + 1] == '<')
			|| (s[*i] == '>' && s[*i + 1] == '>'))
			*i += 2;
		else
			(*i)++;
	}
	else
	{
		*in_s = 0;
		*in_d = 0;
		while (s[*i] && is_token_char(s[*i], *in_s, *in_d))
		{
			handle_quotes(s[*i], in_s, in_d);
			(*i)++;
		}
	}
}

static int	count_tokens(const char *s)
{
	size_t	i;
	int		count;
	int		in_squote;
	int		in_dquote;

	i = 0;
	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (!s[i])
			break ;
		count++;
		process_token(s, &i, &in_squote, &in_dquote);
	}
	if (in_squote)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		return (-1);
	}
	if (in_dquote)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `\"'\n", 2);
		return (-1);
	}
	return (count);
}

static char	*get_next_token(const char *s, size_t *i)
{
	size_t	start;
	int		in_squote;
	int		in_dquote;

	in_dquote = 0;
	in_squote = 0;
	skip_whitespace(s, i);
	start = *i;
	process_token(s, i, &in_squote, &in_dquote);
	return (ft_substr(s, start, *i - start));
}

static char	**allocate_tokens(int count)
{
	char	**tokens;

	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	return (tokens);
}

static int	fill_tokens(char **tokens, const char *s, int count)
{
	int		t;
	size_t	i;

	t = 0;
	i = 0;
	while (t < count)
	{
		tokens[t] = get_next_token(s, &i);
		if (!tokens[t])
		{
			free_str(tokens);
			return (0);
		}
		t++;
	}
	tokens[t] = NULL;
	return (1);
}

char	**shell_split(char const *s)
{
	int		count;
	char	**tokens;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	if (count < 0)
		return (NULL);
	tokens = allocate_tokens(count);
	if (!tokens)
		return (NULL);
	if (!fill_tokens(tokens, s, count))
		return (NULL);
	return (tokens);
}

static int	is_redir(const char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<") == 0)
		return (1);
	if (ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0)
		return (1);
	return (0);
}

static char	*unquote_str(char *str)
{
	int		len;
	char	*unquoted;
	int		is_quoted;

	len = ft_strlen(str);
	is_quoted = (len >= 2 && ((str[0] == '\''
					&& str[len - 1] == '\'')
				|| (str[0] == '"'
					&& str[len - 1] == '"')));
	if (is_quoted)
	{
		unquoted = ft_substr(str, 1, len - 2);
		return (unquoted);
	}
	return (ft_strdup(str));
}

static void	handle_heredoc_redir(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	char	*unquoted_delimiter;

	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		cmd->heredoc_expand = 0;
	else
		cmd->heredoc_expand = 1;
	unquoted_delimiter = unquote_str(delimiter);
	cmd->in = handle_heredoc(unquoted_delimiter,
			cmd->heredoc_expand, shell);
	free(unquoted_delimiter);
}

static void	handle_redir(t_cmd *cmd, char **tokens, int *i, int end,
		t_shell *shell)
{
	if (*i + 1 >= end)
		return;
	if (ft_strcmp(tokens[*i], ">") == 0)
		cmd->out = open(tokens[*i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(tokens[*i], ">>") == 0)
		cmd->out = open(tokens[*i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(tokens[*i], "<") == 0)
		cmd->in = open(tokens[*i + 1], O_RDONLY);
	else if (ft_strcmp(tokens[*i], "<<") == 0)
		handle_heredoc_redir(cmd, tokens[*i + 1], shell);
	if (cmd->in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tokens[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (cmd->out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tokens[*i + 1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	(*i)++;
}

static int	count_args(char **tokens, int start, int end)
{
	int	argc;
	int	i;

	argc = 0;
	i = start;
	while (i < end)
	{
		if (is_redir(tokens[i]))
			i++;
		else
			argc++;
		i++;
	}
	return (argc);
}

static t_cmd	*init_cmd(int argc)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->in = STDIN_FILENO;
	cmd->out = STDOUT_FILENO;
	cmd->heredoc_expand = 1;
	cmd->next = NULL;
	cmd->flag = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!cmd->flag)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

static void	populate_cmd(t_cmd *cmd, char **tokens, int start, int end,
		t_shell *shell)
{
	int		i;
	int		j;

	i = start;
	j = 0;
	while (i < end)
	{
		if (is_redir(tokens[i]))
			handle_redir(cmd, tokens, &i, end, shell);
		else
		{
			cmd->flag[j] = ft_strdup(tokens[i]);
			j++;
		}
		i++;
	}
	cmd->flag[j] = NULL;
	cmd->cmd = cmd->flag[0];
}

static t_cmd	*create_cmd_from_tokens(char **tokens, int start, int end,
	t_shell *shell)
{
	t_cmd	*cmd;
	int		argc;

	if (start >= end)
		return (NULL);
	argc = count_args(tokens, start, end);
	if (argc == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	cmd = init_cmd(argc);
	if (!cmd)
		return (NULL);
	populate_cmd(cmd, tokens, start, end, shell);
	return (cmd);
}

static void free_tokens(char **tokens)
{
	int i;

	i = 0;
	if (!tokens)
		return;
		
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	process_pipe_token(t_cmd **cmd_list, char **tokens,
	int *start, int i, t_shell *shell)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd_from_tokens(tokens, *start, i, shell);
	if (!new_cmd)
	{
		ft_putstr_fd("minishell: syntax error near `|'\n", 2);
		free_tokens(tokens);
		free_cmds(*cmd_list);
		return (0);
	}
	add_cmd_node_back(cmd_list, new_cmd);
	*start = i + 1;
	return (1);
}

static t_cmd	*finalize_parsing(t_cmd *cmd_list, char **tokens,
	int start, int i, t_shell *shell)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd_from_tokens(tokens, start, i, shell);
	if (!new_cmd && cmd_list)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		free_tokens(tokens);
		free_cmds(cmd_list);
		return (NULL);
	}
	if (new_cmd)
		add_cmd_node_back(&cmd_list, new_cmd);
	free_tokens(tokens);
	return (cmd_list);
}

static t_cmd	*process_tokens(char **tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	int		i;
	int		start;

	cmd_list = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (!process_pipe_token(&cmd_list, tokens, &start, i,
					shell))
				return (NULL);
		}
		i++;
	}
	return (finalize_parsing(cmd_list, tokens, start, i, shell));
}

t_cmd	*parse_line(char *line, t_shell *shell)
{
	char	**tokens;

	if (!line)
		return (NULL);
	tokens = shell_split(line);
	if (!tokens)
	{
		shell->last_exit_status = 2;
		return (NULL);
	}
	if (!tokens[0])
	{
		free(tokens);
		return (NULL);
	}
	return (process_tokens(tokens, shell));
}