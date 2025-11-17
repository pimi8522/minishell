/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:52:30 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/17 16:52:19 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redir	*new_redir_node(t_token_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	return (new);
}

void	free_redirs(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = (t_redir *)content;
	free(redir->file);
	free(redir);
}

int	handle_redirection(t_cmd *cmd, t_token **current, t_shell *shell)
{
	t_token_type	redir_type;
	t_redir			*redir;
	t_list			*new_redir_list_node;

	redir_type = (*current)->type;
	*current = (*current)->next;
	if (!*current || (*current)->type != T_WORD)
	{
		print_syn_error("newline", shell);
		return (1);
	}
	redir = new_redir_node(redir_type, ft_strdup((*current)->value));
	if (!redir || !redir->file)
	{
		if (redir)
			free(redir);
		return (1);
	}
	new_redir_list_node = ft_lstnew(redir);
	if (!new_redir_list_node)
	{
		free(redir->file);
		free(redir);
		return (1);
	}
	ft_lstadd_back(&cmd->redirs, new_redir_list_node);
	return (0);
}
