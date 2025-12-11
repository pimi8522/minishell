/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:17:00 by refactor          #+#    #+#             */
/*   Updated: 2025/11/21 16:17:00 by refactor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	map_redir_mode(t_token_type ttype)
{
	if (ttype == T_LESS)
		return (REDIN);
	if (ttype == T_GREAT)
		return (REDOUT);
	if (ttype == T_DLESS)
		return (HDOC);
	if (ttype == T_DGREAT)
		return (APPEND);
	return (REDIN);
}

//ver se tem aspas ou plicas
static bool	is_quoted(const char *s)
{
	size_t	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"')
			|| (s[0] == '\'' && s[len - 1] == '\'')))
		return (true);
	return (false);
}

//detetar o tipo de aspas
static t_quote_type	quote_type_of(const char *s)
{
	size_t	len;

	if (!s)
		return (Q_NONE);
	len = ft_strlen(s);
	if (len >= 2 && s[0] == '"' && s[len - 1] == '"')
		return (Q_DOUBLE);
	if (len >= 2 && s[0] == '\'' && s[len - 1] == '\'')
		return (Q_SINGLE);
	return (Q_NONE);
}

//tirar quotes
static char	*strip_surrounding_quotes(const char *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"')
			|| (s[0] == '\'' && s[len - 1] == '\'')))
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}

void	free_input_list(t_input *list)
{
	t_input	*next;
	int		i;
	int		j;

	while (list)
	{
		next = list->next;
		/* free argv */
		i = 0;
		while (list->argv && list->argv[i])
		{
			free(list->argv[i]);
			i++;
		}
		free(list->argv);
		/* free parallel quotes array */
		free(list->arg_quotes);
		/* free infiles */
		if (list->infiles)
		{
			j = 0;
			while (list->infiles[j].filename)
			{
				free(list->infiles[j].filename);
				j++;
			}
			free(list->infiles);
		}
		/* free outfiles */
		if (list->outfiles)
		{
			j = 0;
			while (list->outfiles[j].filename)
			{
				free(list->outfiles[j].filename);
				j++;
			}
			free(list->outfiles);
		}
		free(list);
		list = next;
	}
}

//quantos argumentos e redirecionamentos tem em cada segmento (ate um pipe)
static void	count_segment(t_lex_token *tok,
	int *argc, int *in_count, int *out_count)
{
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			(*argc)++;
		else if (is_redir_token(tok->type))
		{
			if (tok->type == T_LESS || tok->type == T_DLESS)
				(*in_count)++;
			else
				(*out_count)++;
			if (tok->next)
				tok = tok->next;
		}
		if (tok)
			tok = tok->next;
	}
}


static int	fill_segment(t_input *seg, t_lex_token **cursor)
{
	int			ai;
	int			ii;
	int			oi;
	t_lex_token	*tok;

	ai = 0;
	ii = 0;
	oi = 0;
	tok = *cursor;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
		{
			seg->argv[ai] = strip_surrounding_quotes(tok->value);
			if (!seg->argv[ai])
				return (1);
			seg->arg_quotes[ai] = quote_type_of(tok->value);
			ai++;
		}
		else if (is_redir_token(tok->type))
		{
			if (!tok->next || tok->next->type != T_WORD)
				return (1);
			if (tok->type == T_LESS || tok->type == T_DLESS)
			{
				seg->infiles[ii].filename =
					strip_surrounding_quotes(tok->next->value);
				if (!seg->infiles[ii].filename)
					return (1);
				seg->infiles[ii].mode = map_redir_mode(tok->type);
				seg->infiles[ii].quoted = is_quoted(tok->next->value);
				ii++;
			}
			else
			{
				seg->outfiles[oi].filename =
					strip_surrounding_quotes(tok->next->value);
				if (!seg->outfiles[oi].filename)
					return (1);
				seg->outfiles[oi].mode = map_redir_mode(tok->type);
				seg->outfiles[oi].quoted = is_quoted(tok->next->value);
				oi++;
			}
			tok = tok->next;
		}
		tok = tok->next;
	}
	/* NULL terminators */
	seg->argv[ai] = NULL;
	seg->arg_quotes[ai] = Q_NONE; /* sentinel to match argv terminator */
	seg->infiles[ii].filename = NULL;
	seg->outfiles[oi].filename = NULL;
	*cursor = tok;
	return (0);
}

static t_input	*alloc_segment(int argc, int in_count, int out_count)
{
	t_input	*seg;

	seg = (t_input *)ft_calloc(1, sizeof(t_input));
	if (!seg)
		return (NULL);
	seg->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!seg->argv)
		return (free(seg), NULL);
	seg->arg_quotes = (t_quote_type *)ft_calloc(argc + 1, sizeof(t_quote_type));
	if (!seg->arg_quotes)
		return (free(seg->argv), free(seg), NULL);
	seg->infiles = (t_file *)ft_calloc(in_count + 1, sizeof(t_file));
	if (!seg->infiles)
		return (free(seg->arg_quotes), free(seg->argv), free(seg), NULL);
	seg->outfiles = (t_file *)ft_calloc(out_count + 1, sizeof(t_file));
	if (!seg->outfiles)
		return (free(seg->infiles), free(seg->arg_quotes), free(seg->argv), free(seg), NULL);
	seg->next = NULL;
	return (seg);
}

static void	append_segment(t_input **head, t_input *new_seg)
{
	t_input	*cur;

	if (!*head)
	{
		*head = new_seg;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_seg;
}

t_input	*parser_input(char *line, t_shell *shell)
{
	t_lex_token	*tokens;
	t_lex_token	*cur;
	t_input		*list;
	t_input		*seg;
	int			argc;
	int			in_count;
	int			out_count;

	if (!line)
		return (NULL);
	tokens = lexer(line);
	if (!tokens)
	{
		shell->last_exit_status = 2;
		return (NULL);
	}
	if (check_syntax(tokens, shell))
	{
		ft_clear_token_list(&tokens);
		return (NULL);
	}
	list = NULL;
	cur = tokens;
	while (cur)
	{
		argc = 0;
		in_count = 0;
		out_count = 0;
		count_segment(cur, &argc, &in_count, &out_count);
		seg = alloc_segment(argc, in_count, out_count);
		if (!seg || fill_segment(seg, &cur))
		{
			free_input_list(seg);
			free_input_list(list);
			ft_clear_token_list(&tokens);
			shell->last_exit_status = 2;
			return (NULL);
		}
//secção dos pipes adjacentes com espaços entre eles
		if (seg->argv[0] == NULL
			&& (!seg->infiles || seg->infiles[0].filename == NULL)
			&& (!seg->outfiles || seg->outfiles[0].filename == NULL))
		{
			print_syn_error("|", shell);
			free_input_list(seg);
			free_input_list(list);
			ft_clear_token_list(&tokens);
			shell->last_exit_status = 2;
			return (NULL);
		}
		append_segment(&list, seg);
		if (cur && cur->type == T_PIPE)
			cur = cur->next;
	}
	ft_clear_token_list(&tokens);
	return (list);
}
