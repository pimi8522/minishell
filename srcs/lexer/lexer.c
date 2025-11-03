/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:18:46 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/03 18:32:19 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*new_token(char *value, t_token_type type)
{
    t_token	*token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

static void	add_token_back(t_token **list, t_token *new)
{
    t_token	*current;

    if (!list || !new)
        return;
    if (!*list)
    {
        *list = new;
        return;
    }
    current = *list;
    while (current->next)
        current = current->next;
    current->next = new;
}

void	ft_clear_token_list(t_token **list)
{
    t_token	*current;
    t_token	*next;

    if (!list)
        return;
    current = *list;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    *list = NULL;
}

static int	handle_separator(const char **line_ptr, t_token **token_list)
{
    const char	*line = *line_ptr;
    t_token_type	type;
    char		*value;
    int			len;

    len = 1;
    if (!ft_strncmp(line, "<<", 2))
        (void)(len = 2, type = T_DLESS);
    else if (!ft_strncmp(line, ">>", 2))
        (void)(len = 2, type = T_DGREAT);
    else if (!ft_strncmp(line, "&&", 2))
        (void)(len = 2, type = T_AND);
    else if (!ft_strncmp(line, "||", 2))
        (void)(len = 2, type = T_OR);
    else if (*line == '<')
        type = T_LESS;
    else if (*line == '>')
        type = T_GREAT;
    else if (*line == '|')
        type = T_PIPE;
    else if (*line == '(')
        type = T_O_PARENT;
    else if (*line == ')')
        type = T_C_PARENT;
    else
        return (0);
    value = ft_substr(line, 0, len);
    if (!value || !new_token(value, type))
        return (free(value), 0);
    add_token_back(token_list, new_token(value, type));
    *line_ptr += len;
    return (1);
}

static int	handle_word(const char **line_ptr, t_token **token_list)
{
    const char	*start;
    size_t		i;
    char		*value;

    start = *line_ptr;
    i = 0;
    while (start[i] && !is_separator_char(start[i]))
    {
        if (is_quote(start[i]))
        {
            if (!ft_skip_quotes(start, &i))
                return (ft_print_quote_err(start[i]), 0);
        }
        else
            i++;
    }
    value = ft_substr(start, 0, i);
    if (!value || !new_token(value, T_WORD))
        return (free(value), 0);
    add_token_back(token_list, new_token(value, T_WORD));
    *line_ptr += i;
    return (1);
}

t_token	*lexer(const char *s)
{
    t_token	*token_list;
    int		erro_check;

    if (!s)
        return (NULL);
    token_list = NULL;
    erro_check = 0;
    while (*s)
    {
        skip_whitespace(s, (size_t *) &s);
        if (!*s)
            break ;
        if (is_separator_char(*s))
            erro_check = handle_separator(&s, &token_list);
        else
            erro_check = handle_word(&s, &token_list);
        if (erro_check == 0)
        {
            ft_clear_token_list(&token_list);
            return (NULL);
        }
    }
    return (token_list);
}
