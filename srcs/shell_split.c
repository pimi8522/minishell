/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:28:57 by miduarte &        #+#    #+#             */
/*   Updated: 2025/08/29 16:55:07 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_space(char c)
{
	int r;

	r = 0;
	if (c == ' ' || c == '\t' || c == '\n')
		r = 1;
	if (c == '\r' || c == '\v' || c == '\f')
		r = 1;
	return (r);
}

static void skip_ws(const char *s, size_t *i)
{
	while (s[*i] && is_space(s[*i]))
		*i += 1;
}

static int pass1_len(const char *s, size_t *i, int *qs, int *qd)
{
	size_t  start;
	char    c;

	start = *i;
	while (s[*i])
	{
		c = s[*i];
		if (c == '\'' && !*qd)
		{
			*qs = !*qs;
			*i += 1;
			continue ;
		}
		if (c == '"' && !*qs)
		{
			*qd = !*qd;
			*i += 1;
			continue ;
		}
		if (!*qs && !*qd && is_space(c))
			break ;
		*i += 1;
	}
	if (*qs || *qd)
		return (-1);
	return ((int)(*i - start));
}

static int pass1_count(const char *s, size_t *i)
{
	int     count;
	int     qs;
	int     qd;
	int     len;

	count = 0;
	qs = 0;
	qd = 0;
	while (s[*i])
	{
		skip_ws(s, i);
		if (!s[*i])
			break ;
		len = pass1_len(s, i, &qs, &qd);
		if (len < 0)
			return (-1);
		count += 1;
	}
	return (count);
}

static char *copy_token(const char *s, size_t *i)
{
	size_t  j;
	size_t  k;
	int     qs;
	int     qd;
	char    *dst;
	char    c;

	qs = 0;
	qd = 0;
	j = *i;
	while (s[j] && (qs || qd || !is_space(s[j])))
	{
		if (s[j] == '\'' && !qd)
			qs = !qs;
		else if (s[j] == '"' && !qs)
			qd = !qd;
		j += 1;
	}
	dst = (char *)do_malloc((j - *i) + 1);
	k = 0;
	while (*i < j)
	{
		c = s[*i];
		if (c == '\'' && !qd)
			qs = !qs;
		else if (c == '"' && !qs)
			qd = !qd;
		else
		{
			dst[k] = c;
			k += 1;
		}
		*i += 1;
	}
	dst[k] = '\0';
	return (dst);
}

char **shell_split(char const *s)
{
	size_t  i;
	int     n;
	char    **arr;
	int     k;
	
	if (!s)
		return (NULL);
	i = 0;
	n = pass1_count(s, &i);
	if (n < 0)
		return (NULL);

	arr = (char **)do_malloc(sizeof(char *) * (n + 1));
	k = 0;
	i = 0;
	while (s[i])
	{
		skip_ws(s, &i);
		if (!s[i])
			break ;
		arr[k] = copy_token(s, &i);
		k += 1;
	}
	arr[k] = NULL;
	return (arr);
}
