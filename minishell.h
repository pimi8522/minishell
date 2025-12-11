/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/21 16:17:37 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

# include "libft/libft.h"
#define WHITESPACE	"\t\n\v\f\r "

typedef struct s_cmd
{
	char			*cmd;
	char			**flag; //os comandos em si separados
	t_list			*redirs;
	int				fd[2];
	int				heredoc_expand;
	struct s_cmd	*next;
} t_cmd;

typedef enum e_token_type
{
    T_WORD,      // A regular word or quoted string
    T_PIPE,      // |
    T_LESS,      // < (redirect in)
    T_GREAT,     // > (redirect out)
    T_DLESS,     // << (heredoc)
    T_DGREAT,    // >> (append out)
    T_AND,       // && (for parser)
    T_OR,        // || (for parser)
    T_O_PARENT,  // (  (for parser)
    T_C_PARENT,  // )  (for parser)
}   t_token_type;

/*
** New redirection/file mode enum separate from lexer token types.
** (Requested output representation)
*/
typedef enum e_token
{
    REDIN,   // <
    REDOUT,  // >
    HDOC,    // <<
    APPEND   // >>
}   t_token;

/*
** manter conta do tipo de aspas cortadas em cada argumento
*/
typedef enum e_quote_type
{
    Q_NONE = 0,
    Q_SINGLE,
    Q_DOUBLE
}   t_quote_type;

/*
** File representation for input/output redirections
*/
typedef struct s_file
{
    char    *filename;
    t_token mode;
    bool    quoted;
}   t_file;

/*
** Parsed command segment (one pipeline component)
** argv: NULL-terminated argument vector
** infiles/outfiles: dynamic arrays terminated by filename == NULL (or tracked separately)
** next: singly linked list to represent a pipeline
*/
typedef struct s_input
{
    char            **argv;
    t_quote_type    *arg_quotes;    // parallel array: quote type per argv[i], NULL-terminated with Q_NONE sentinel
    t_file          *infiles;
    t_file          *outfiles;
    struct s_input  *next;
}   t_input;


typedef struct s_redir
{
	t_token_type	type;
	char			*file;
}	t_redir;



// structs para o lexer

typedef struct s_lex_token
{
    char                *value;
    t_token_type        type;
    struct s_lex_token  *next;
}   t_lex_token;

// - ------------ -- --- Para o parser

typedef enum e_node_type
{
    N_PIPE,
    N_AND,
    N_OR,
    N_CMD
}	t_node_type;

//---------------

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;


//shell struct
typedef struct s_shell
{
	int		last_exit_status;
	t_env	*env_list;
}	t_shell;

/*
** ANSI Color codes for terminal output formatting:
** Y    - Yellow
** G    - Green
** C    - Cyan
** RED  - Red
** RST  - Reset to default color
*/
#define Y		"\1\033[1;33m\2"
#define G		"\1\033[1;32m\2"
#define C 		"\1\033[1;36m\2"
#define RED		"\1\033[1;31m\2"
#define RST 	"\1\033[0m\2"


/*
** srcs/utils.c
*/
char	*get_cwd(char *buf, size_t size);
void	*do_malloc(size_t size);
void	print_banner(void);

/*
** srcs/signals.c
*/
void	sigint_handler(int signo);
void	setup_interactive_signals(void);
void	setup_exec_signals(void);
void	heredoc_sigint_handler(int signo);

/*
** srcs/history.c
*/
int		init_shell_history(void);
void	save_shell_history(void);

/*
** srcs/lexer/lexer.c
*/
t_lex_token	*lexer(char const *s);
void	ft_clear_token_list(t_lex_token **list);
int		is_separator_char(char c);
void	skip_whitespace(const char *s, size_t *i);
int		is_quote(char c);
bool	ft_skip_quotes(const char *line, size_t *i);
void	ft_print_quote_err(char c);

/*
** srcs/parser/parser.c
*/
t_cmd	*parser(char *line, t_shell *shell);
t_cmd	*parse_tokens(t_lex_token *tokens, t_shell *shell);
t_cmd	*new_cmd_node(char *cmd, char **flags);
void	add_cmd_node_back(t_cmd **cmd_list_head, t_cmd *new_node);
void	free_cmds(t_cmd *cmd_list);
int		check_syntax(t_lex_token *tokens, t_shell *shell);
int		count_args(t_lex_token *tokens);
int		print_syn_error(char *str, t_shell *shell);
int		is_redir_token(t_token_type t);
t_lex_token	*get_last_token(t_lex_token *token_list);

/*
** Future parser (pipeline) output helpers (to be implemented)
*/
t_input		*parser_input(char *line, t_shell *shell);
void		free_input_list(t_input *list);

/*
** srcs/parser/redirs.c
*/
int		handle_redirection(t_cmd *cmd, t_lex_token **current, t_shell *shell);
void	free_redirs(void *content);


#endif