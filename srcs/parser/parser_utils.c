/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte & adores@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:44:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/04 15:15:44 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_syn_error()
{
	//find way to write which error it was with the "near" thing
}

int is_redir_token (t_token_type t)
{
	return (t == T_LESS || t == T_GREAT || t == T_DLESS || t == T_DGREAT);
}

int is_invalid_token (t_token_type t)
{
	if (t == T_AND || t == T_OR)
		return print_syn_error();
	else if (t == T_C_PARENT)
	{
		//skip to see if there is match parenthesis
		//detect if there is empty bracket pack
	}
	
}