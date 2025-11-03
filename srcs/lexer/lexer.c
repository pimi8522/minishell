/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:18:46 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/03 14:21:41 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_token_len_and_skip(const char *s, size_t *i)
{
    size_t	start;
    char	c;

    start = *i;
    c = s[*i];
    if (is_separator_char(c) && !is_quote(c))
    {
        if ((c == '<' && s[*i + 1] == '<') || (c == '>' && s[*i + 1] == '>'))
            *i += 2;
        else
            (*i)++;
    }
    else if (is_quote(c))
    {
        if (!ft_skip_quotes(s, i))
        {
            ft_print_quote_err(c);
            return (0);
        }
    }
    else
    {
        while (s[*i] && !is_separator_char(s[*i]))
            (*i)++;
    }
    return (*i - start);
}

static int	count_tokens(const char *s)
{
    size_t	i;
    int		count;

    i = 0;
    count = 0;
    while (s[i])
    {
        skip_whitespace(s, &i);
        if (!s[i])
            break ;
        if (get_token_len_and_skip(s, &i) == 0)
            return (-1);
        count++;
    }
    return (count);
}

static int	fill_tokens(char **tokens, const char *s, int count)
{
    int		t;
    size_t	i;
    size_t	start;
    size_t	len;

    t = 0;
    i = 0;
    while (t < count)
    {
        skip_whitespace(s, &i);
        start = i;
        len = get_token_len_and_skip(s, &i);
        if (len == 0)
            continue ;
        tokens[t] = ft_substr(s, start, len);
        if (!tokens[t])
        {
            free_str_array(tokens);
            return (0);
        }
        t++;
    }
    tokens[t] = NULL;
    return (1);
}

char	**lexer(char const *s)
{
    int		count;
    char	**tokens;

    if (!s)
        return (NULL);
    count = count_tokens(s);
    if (count < 0)
        return (NULL);
    tokens = (char **)malloc(sizeof(char *) * (count + 1));
    if (!tokens)
        return (NULL);
    if (!fill_tokens(tokens, s, count))
        return (NULL);
    return (tokens);
}
