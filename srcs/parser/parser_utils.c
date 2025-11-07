/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:44:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/07 18:46:28 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_syn_error(char *str, t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_exit_status = 2;
	return (1);
}

int	is_redir_token(t_token_type t)
{
	return (t == T_LESS || t == T_GREAT || t == T_DLESS || t == T_DGREAT);
}

t_token	*get_last_token(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_WORD)
			count++;
		else if (is_redir_token(tokens->type))
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (count);
}

static bool	check_leading_pipe(t_token *token_list, t_shell *shell)
{
	if (token_list->type == T_PIPE)
	{
		return (print_syn_error("|", shell), true);
	}
	return (false);
}

static bool	check_trailing_pipe(t_token *token_list, t_shell *shell)
{
	t_token	*last_token;

	last_token = get_last_token(token_list);
	if (last_token->type == T_PIPE)
	{
		return (print_syn_error("|", shell), true);
	}
	return (false);
}

static bool	check_bonus_parts(t_token *token_list, t_shell *shell)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == T_AND || current->type == T_OR
			|| current->type == T_O_PARENT || current->type == T_C_PARENT)
		{
			return (print_syn_error(current->value, shell), true);
		}
		current = current->next;
	}
	return (false);
}

static bool	validate_redirections(t_token *token_list, t_shell *shell)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!current->next)
				return (print_syn_error("newline", shell), true);
			if (current->next->type != T_WORD)
				return (print_syn_error(current->next->value, shell), true);
		}
		current = current->next;
	}
	return (false);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	if (check_leading_pipe(tokens, shell))
		return (1);
	if (check_trailing_pipe(tokens, shell))
		return (1);
	if (check_bonus_parts(tokens, shell))
		return (1);
	if (validate_redirections(tokens, shell))
		return (1);
	return (0);
}