/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:50:06 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/11 17:57:01 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *filename, t_token_type type)
{
	int	fd;

	fd = -1;
	if (type == T_LESS)
		fd = open(filename, O_RDONLY);
	else if (type == T_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == T_DGREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(filename);
	}
	return (fd);
}


int	handle_redirection(t_cmd *cmd, t_token **current, t_shell *shell)
{
	t_token_type	type;
	char			*filename;
	int				fd;

	type = (*current)->type;
	filename = (*current)->next->value;
	if (type == T_DLESS)
		fd = handle_heredoc(filename, 0, shell);
	else
		fd = open_file(filename, type);
	if (fd == -1)
		return (1);
	if (type == T_LESS || type == T_DLESS)
	{
		if (cmd->in != STDIN_FILENO)
			close(cmd->in);
		cmd->in = fd;
	}
	else if (type == T_GREAT || type == T_DGREAT)
	{
		if (cmd->out != STDOUT_FILENO)
			close(cmd->out);
		cmd->out = fd;
	}
	*current = (*current)->next->next;
	return (0);
}
