/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte & adores@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:44:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/06 15:48:48 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

bool check_leading_pipe (t_token *token_list, t_shell *shell)
{
	if (token_list->type == T_PIPE) //leading pipe é erro nerd
	{
		print_syn_error("|", shell);
		return (true);
	}
	return (false);
}

bool check_trailing_pipe (t_token *token_list, t_shell *shell)
{
	t_token	*last_token;

	last_token = get_last_token(token_list);
	if (last_token->type == T_PIPE) //trailing pipe é erro too
	{
		print_syn_error("|", shell);
		return (true);
	}
	return (false);
}

bool check_and_or(t_token *token_list, t_shell *shell) // isto só checka os && e || que são bonus and we aint fucking wid that
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == T_AND || current->type == T_OR)
		{
			print_syn_error(current->value, shell);
			return (true);
		}
		current = current->next;
	}
	return (false);
}
bool	validate_parentheses(t_token *token_list, t_shell *shell)
{
	int		open_parentheses;
	t_token	*current;

	open_parentheses = 0;
	current = token_list;
	while (current)
	{
		if (current->type == T_O_PARENT)
		{
			open_parentheses++;
			if (current->next && current->next->type == T_C_PARENT) //pra verificar coisas tipo () (empty subshells)
			{
				print_syn_error(")", shell);
				return (true);
			}
		}
		else if (current->type == T_C_PARENT)
			open_parentheses--;
		if (open_parentheses < 0) //if encontra um ) antes de um ( somehow
		{
			print_syn_error(")", shell);
			return (true);
		}
		current = current->next;
	}
	if (open_parentheses != 0)
	{
		print_syn_error(")", shell);
		return (true);
	}
	return (false);
}


bool	validate_redirections(t_token *token_list, t_shell *shell)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!current->next)
			{
				print_syn_error("newline", shell);
				return (true);
			}
			if (current->next->type != T_WORD)
			{
				print_syn_error(current->next->value, shell);
				return (true);
			}
		}
		current = current->next;
	}
	return (false);
}

t_cmd parse_into_commands (t_token **tok, t_shell shell)
{
	t_cmd *cmd;
	
	//while token_list =! de pipe, meter no cmd i would assume
	//cada node da cmd probably eh um comando diferente
}