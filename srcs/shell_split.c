/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:28:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/02 17:25:00 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retorna 1 se for whitespace
static int is_blank(char c)
{
	int r;

	r = 0;
	if (c == ' ' || c == '\t' || c == '\n')
		r = 1;
	if (c == '\r' || c == '\v' || c == '\f')
		r = 1;
	return (r);
}

// salta whitespace
static void skip_blanks(const char *s, size_t *i)
{
	while (s[*i] && is_blank(s[*i]))
		*i += 1;
}

// retorna o tamanho do token e valida aspas
//squote - plicas
//dquote - aspas
static int span_token(const char *s, size_t *i,
					  int *squote, int *dquote)
{
	size_t  start;
	char    c;

	start = *i;
	while (s[*i])
	{
		c = s[*i];
		if (c == '\'' && !*dquote)
		{
			*squote = !*squote;
			*i += 1;
			continue ;
		}
		if (c == '"' && !*squote)
		{
			*dquote = !*dquote;
			*i += 1;
			continue ;
		}
		if (!*squote && !*dquote && is_blank(c))
			break ;
		*i += 1;
	}
	if (*squote || *dquote)
		return (-1);
	return ((int)(*i - start));
}

// conta tokens (primeira passagem)
static int count_tokens(const char *s, size_t *i)
{
	int count;
	int squote;
	int dquote;
	int span;

	count = 0;
	squote = 0;
	dquote = 0;
	while (s[*i])
	{
		skip_blanks(s, i);
		if (!s[*i])
			break ;
		span = span_token(s, i, &squote, &dquote);
		if (span < 0)
			return (-1);
		count += 1;
	}
	return (count);
}

// encontra o fim do token respeitando aspas
static size_t find_token_end(const char *s, size_t start)
{
	size_t  end;
	int     squote;
	int     dquote;

	end = start;
	squote = 0;
	dquote = 0;
	while (s[end] && (squote || dquote || !is_blank(s[end])))
	{
		if (s[end] == '\'' && !dquote)
			squote = !squote;
		else if (s[end] == '"' && !squote)
			dquote = !dquote;
		end += 1;
	}
	return (end);
}

// copia o span removendo aspas e avança *i até end (segunda passagem)
static char *copy_span_unquoted(const char *s, size_t *i, size_t end)
{
	size_t  out;
	int     squote;
	int     dquote;
	char    *token;
	char    c;

	token = (char *)do_malloc((end - *i) + 1);
	out = 0;
	squote = 0;
	dquote = 0;
	while (*i < end)
	{
		c = s[*i];
		if (c == '\'' && !dquote)
			squote = !squote;
		else if (c == '"' && !squote)
			dquote = !dquote;
		else
		{
			token[out] = c;
			out += 1;
		}
		*i += 1;
	}
	token[out] = '\0';
	return (token);
}

// cria o token removendo aspas
static char *copy_unquoted_token(const char *s, size_t *i)
{
	size_t  end;

	end = find_token_end(s, *i);
	return (copy_span_unquoted(s, i, end));
}

char **shell_split(char const *s)
{
	size_t  i;
	int     count;
	char    **tokens;
	int     t;
    
	if (!s)
		return (NULL);
	i = 0;
	count = count_tokens(s, &i);
	if (count < 0)
		return (NULL);

	tokens = (char **)do_malloc(sizeof(char *) * (count + 1));
	t = 0;
	i = 0;
	while (s[i])
	{
		skip_blanks(s, &i);
		if (!s[i])
			break ;
		tokens[t] = copy_unquoted_token(s, &i);
		t += 1;
	}
	tokens[t] = NULL;
	return (tokens);
}

//todo - classificar operadores e dividir em operadores e argumentos n shit