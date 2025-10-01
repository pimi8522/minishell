/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:28:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/01 19:00:00 by Roo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// verifica se um caractere é um metacaractere (|, <, >)
static int	is_meta_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// avança o índice `i` para ignorar o whitespace
static void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] && ft_strchr(WHITESPACE, s[*i]))
		(*i)++;
}

// conta o número de tokens na string de input
static int	count_tokens(const char *s)
{
	int		count;
	size_t	i;
	int		in_squote;
	int		in_dquote;

	count = 0;
	i = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (!s[i])
			break ;
		count++;
		if (is_meta_char(s[i]))
		{
			if ((s[i] == '<' && s[i + 1] == '<')
				|| (s[i] == '>' && s[i + 1] == '>'))
				i += 2;
			else
				i++;
		}
		else
		{
			in_squote = 0;
			in_dquote = 0;
			while (s[i] && (in_squote || in_dquote || \
				(!ft_strchr(WHITESPACE, s[i]) && !is_meta_char(s[i]))))
			{
				if (s[i] == '\'' && !in_dquote)
					in_squote = !in_squote;
				else if (s[i] == '"' && !in_squote)
					in_dquote = !in_dquote;
				i++;
			}
		}
	}
	return (count);
}

// extrai o próximo token da string de input
static char	*get_next_token(const char *s, size_t *i)
{
	size_t	start;
	int		in_squote;
	int		in_dquote;

	skip_whitespace(s, i);
	start = *i;
	if (is_meta_char(s[*i]))
	{
		if ((s[*i] == '<' && s[*i + 1] == '<')
			|| (s[*i] == '>' && s[*i + 1] == '>'))
			*i += 2;
		else
			(*i)++;
	}
	else
	{
		in_squote = 0;
		in_dquote = 0;
		while (s[*i] && (in_squote || in_dquote || \
			(!ft_strchr(WHITESPACE, s[*i]) && !is_meta_char(s[*i]))))
		{
			if (s[*i] == '\'' && !in_dquote)
				in_squote = !in_squote;
			else if (s[*i] == '"' && !in_squote)
				in_dquote = !in_dquote;
			(*i)++;
		}
	}
	return (ft_substr(s, start, *i - start));
}

// função principal que divide a string de input num array de tokens
char	**shell_split(char const *s)
{
	size_t	i;
	int		count;
	char	**tokens;
	int		t;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	if (count < 0)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	t = 0;
	i = 0;
	while (t < count)
	{
		tokens[t] = get_next_token(s, &i);
		if (!tokens[t])
		{
			free_str(tokens);
			return (NULL);
		}
		t++;
	}
	tokens[t] = NULL;
	return (tokens);
}