/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:03 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/06 15:07:07 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(const char *s)
{
	if (!s)
		return (0);
	return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

static char	*unquote_str(char *str)
{
	int		len;
	char	*unquoted;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
	{
		unquoted = ft_substr(str, 1, len - 2);
		return (unquoted);
	}
	return (ft_strdup(str));
}

static void	handle_redir(t_cmd *cmd, char **tokens, int *i, int end,
		t_shell *shell)
{
	char	*delimiter;
	char	*unquoted_delimiter;

	if (*i + 1 >= end)
		return;
	if (ft_strcmp(tokens[*i], ">") == 0)
		cmd->out = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(tokens[*i], ">>") == 0)
		cmd->out = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(tokens[*i], "<") == 0)
		cmd->in = open(tokens[*i + 1], O_RDONLY);
	else if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		delimiter = tokens[*i + 1];
		if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
			cmd->heredoc_expand = 0;
		else
			cmd->heredoc_expand = 1;
		unquoted_delimiter = unquote_str(delimiter);
		cmd->in = handle_heredoc(unquoted_delimiter, cmd->heredoc_expand, shell);
		free(unquoted_delimiter);
	}
	if (cmd->in == -1 || cmd->out == -1)
		perror("minishell");
	(*i)++;
}

static t_cmd	*create_cmd_from_tokens(char **tokens, int start, int end,
		t_shell *shell)
{
	t_cmd	*cmd;
	int		argc;
	int		i;
	int		j;

	if (start >= end)
		return (NULL);
	// 1. Count arguments (non-redirection tokens)
	argc = 0;
	i = start;
	while (i < end)
	{
		if (is_redir(tokens[i]))
			i++; // Skip filename
		else
			argc++;
		i++;
	}
	if (argc == 0)
		return (NULL);
	// 2. Allocate and initialize cmd struct
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
	// 3. Populate cmd with args and handle redirections
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
	cmd->cmd = cmd->flag[0]; // The first argument is the command
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

t_cmd	*parse_line(char *line, t_shell *shell)
{
	char	**tokens;
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	int		i;
	int		start;

	if (!line)
		return (NULL);
	tokens = shell_split(line);
	if (!tokens || !tokens[0])
	{
		free(tokens);
		return (NULL);
	}
	cmd_list = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			new_cmd = create_cmd_from_tokens(tokens, start, i, shell);
			if (!new_cmd)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
					2);
				free_tokens(tokens);
				free_cmds(cmd_list);
				return (NULL);
			}
			add_cmd_node_back(&cmd_list, new_cmd);
			start = i + 1;
		}
		i++;
	}
	new_cmd = create_cmd_from_tokens(tokens, start, i, shell);
	if (!new_cmd && cmd_list)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		free_tokens(tokens);
		free_cmds(cmd_list);
		return (NULL);
	}
	if (new_cmd)
		add_cmd_node_back(&cmd_list, new_cmd);
	free_tokens(tokens);
	return (cmd_list);
}
