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
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] && ft_strchr(WHITESPACE, s[*i]))
		(*i)++;
}

static void	handle_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
	else if (c == '"' && !*in_squote)
		*in_dquote = !*in_dquote;
}

static int	is_token_char(char c, int in_s, int in_d)
{
	if (in_s || in_d)
		return (1);
	if (!ft_strchr(WHITESPACE, c) && !is_meta_char(c))
		return (1);
	return (0);
}

static void	process_token(const char *s, size_t *i, int *in_s, int *in_d)
{
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
		*in_s = 0;
		*in_d = 0;
		while (s[*i] && is_token_char(s[*i], *in_s, *in_d))
		{
			handle_quotes(s[*i], in_s, in_d);
			(*i)++;
		}
	}
}

static int	count_tokens(const char *s)
{
	size_t	i;
	int		count;
	int		in_squote;
	int		in_dquote;

	i = 0;
	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (!s[i])
			break ;
		count++;
		process_token(s, &i, &in_squote, &in_dquote);
	}
	if (in_squote || in_dquote)
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (-1);
	}
	return (count);
}

static char	*get_next_token(const char *s, size_t *i)
{
	size_t	start;
	int		in_squote;
	int		in_dquote;

	in_dquote = 0;
	in_squote = 0;
	skip_whitespace(s, i);
	start = *i;
	process_token(s, i, &in_squote, &in_dquote);
	return (ft_substr(s, start, *i - start));
}

static char	**allocate_tokens(int count)
{
	char	**tokens;

	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	return (tokens);
}

static int	fill_tokens(char **tokens, const char *s, int count)
{
	int		t;
	size_t	i;

	t = 0;
	i = 0;
	while (t < count)
	{
		tokens[t] = get_next_token(s, &i);
		if (!tokens[t])
		{
			free_str(tokens);
			return (0);
		}
		t++;
	}
	tokens[t] = NULL;
	return (1);
}

char	**shell_split(char const *s)
{
	int		count;
	char	**tokens;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	if (count < 0)
		return (NULL);
	tokens = allocate_tokens(count);
	if (!tokens)
		return (NULL);
	if (!fill_tokens(tokens, s, count))
		return (NULL);
	return (tokens);
}
