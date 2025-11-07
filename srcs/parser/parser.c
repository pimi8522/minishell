/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:03 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/07 19:00:16 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*parse_command(t_token **current, t_shell *shell);

t_cmd	*parser(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
	{
		shell->last_exit_status = 2;
		return (NULL);
	}
	cmds = parse_tokens(tokens, shell);
	ft_clear_token_list(&tokens);
	return (cmds);
}

t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{ 
	t_cmd	*cmds;
	t_cmd	*current_cmd;
	t_token	*current_tok;

	if (!tokens)
		return (NULL);
	if (check_syntax(tokens, shell))
		return (NULL);
	cmds = NULL;
	current_tok = tokens;
	while (current_tok)
	{
		current_cmd = parse_command(&current_tok, shell);
		if (!current_cmd)
		{
			free_cmds(cmds);
			return (NULL);
		}
		add_cmd_node_back(&cmds, current_cmd);
		if (current_tok && current_tok->type == T_PIPE)
			current_tok = current_tok->next;
	}
	return (cmds);
}

static t_cmd	*parse_command(t_token **current, t_shell *shell)
{
	t_cmd	*cmd;
	int		argc;
	int		i;

	(void)shell;
	argc = count_args(*current);
	cmd = new_cmd_node(NULL, ft_calloc(argc + 1, sizeof(char *)));
	if (!cmd || !cmd->flag)
		return (NULL);
	i = 0;
	while (*current && (*current)->type != T_PIPE)
	{
		if ((*current)->type == T_WORD)
		{
			cmd->flag[i] = ft_strdup((*current)->value);
			if (!cmd->flag[i])
				return (free_cmds(cmd), NULL);
			i++;
		}
		else if (is_redir_token((*current)->type))
		{
			// Redirection aqaui
			*current = (*current)->next; // Skip redirection token
			if (*current)
				*current = (*current)->next; // Skip filename 
			continue ;
		}
		*current = (*current)->next;
	}
	if (cmd->flag[0])
		cmd->cmd = cmd->flag[0];
	return (cmd);
}
