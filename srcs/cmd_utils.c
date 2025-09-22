/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:40:00 by adores & mi      #+#    #+#             */
/*   Updated: 2025/09/19 14:40:00 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd_node(char *cmd, char **flags)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->flag = flags;
	new_node->in = STDIN_FILENO;
	new_node->out = STDOUT_FILENO;
	new_node->next = NULL;
	return (new_node);
}

void	add_cmd_node_back(t_cmd **cmd_list_head, t_cmd *new_node)
{
	t_cmd	*last;

	if (!cmd_list_head || !new_node)
		return;
	if (*cmd_list_head == NULL)
	{
		*cmd_list_head = new_node;
		return;
	}
	last = *cmd_list_head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void	free_cmds(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		i = 0;
		while (current->flag && current->flag[i])
		{
			free(current->flag[i]);
			i++;
		}
		free(current->flag);
		free(current);
		current = next;
	}
}