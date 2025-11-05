/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:03 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/05 15:05:34 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parser(char *line, t_shell *shell)
{
    t_token	*tokens;
    t_cmd	*cmds;

    // faz o lexer para obter a lista de tokens
    tokens = lexer(line);
    if (!tokens)
 	{
 		shell->last_exit_status = 2;
        return (NULL);
 	}
    // faz o parser para obter a lista de comandos
    cmds = parse_tokens(tokens, shell);
    // liberta a lista de tokens
    ft_clear_token_list(&tokens);
    return (cmds);
}


t_cmd	*parse_tokens(t_token *token_list, t_shell *shell)
{
	if (!token_list)
		return (NULL);
	if (check_leading_pipe(token_list, shell))
		return (NULL);
	if (check_trailing_pipe(token_list, shell))
		return (NULL);
	if (check_and_or(token_list, shell))
		return (NULL);
	if (validate_parentheses(token_list, shell))
		return (NULL);
	return (NULL);
}