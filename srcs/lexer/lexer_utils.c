/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:39:47 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/03 14:20:52 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// verifica se um caractere é um metacaractere (|, <, >, espaço, tab, parênteses)
int	is_separator_char(char c)
{
	if (c == '|' || c == '<' || c == '>' 
        || c == ' ' || c == '\t' || c == ')' || c == '(')
		return (1);
	return (0);
}

void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] && ft_strchr(WHITESPACE, s[*i]))
		(*i)++;
}

int	is_quote(char c)
{
	if ( c == '"' || c == '\'')
		return (1);
	return (0);
}

//se chamada numa aspa avança o indice até a matching aspa. retorna true se tiver match
bool	ft_skip_quotes(const char *line, size_t *i)
{
    char	quote_char;
    size_t	j;

    if (!line || !line[*i])
        return (false);
    quote_char = line[*i];
    j = *i + 1;
    while (line[j])
    {
        if (line[j] == quote_char)
        {
            *i = j + 1;
            return (true);
        }
        if (line[j] == '\\' && line[j + 1])
            j++;
        j++;
    }
    return (false);
}

void	ft_print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}
void	free_str_array(char **arr)
{
    int	i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

