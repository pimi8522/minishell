/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:03 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/29 15:05:03 by miduarte &       ###   ########.fr       */
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

static void	handle_redir(t_cmd *cmd, char **tokens, int *i, int end)
{
	if (*i + 1 >= end)
		return; // Syntax error: redirection with no file
	if (ft_strcmp(tokens[*i], ">") == 0)
		cmd->out = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(tokens[*i], ">>") == 0)
		cmd->out = open(tokens[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(tokens[*i], "<") == 0)
		cmd->in = open(tokens[*i + 1], O_RDONLY);
	else if (ft_strcmp(tokens[*i], "<<") == 0)
		cmd->in = handle_heredoc(tokens[*i + 1]);
	if (cmd->in == -1 || cmd->out == -1)
	{
		perror("minishell"); // Or a custom error message
	}
	(*i)++; // Move past the filename
}

static t_cmd	*create_cmd_from_tokens(char **tokens, int start, int end)
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
			handle_redir(cmd, tokens, &i, end);
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

t_cmd	*parse_line(char *line)
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
			new_cmd = create_cmd_from_tokens(tokens, start, i);
			if (new_cmd)
				add_cmd_node_back(&cmd_list, new_cmd);
			start = i + 1;
		}
		i++;
	}
	new_cmd = create_cmd_from_tokens(tokens, start, i);
	if (new_cmd)
		add_cmd_node_back(&cmd_list, new_cmd);
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (cmd_list);
}
