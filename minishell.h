/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/11/07 18:01:12 by miduarte &       ###   ########.fr       */
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
	char	*cmd;
	char	**flag; //os comandos em si separados
	int		in;
	int		out;
	int		fd[2];
	int		heredoc_expand;
	struct s_cmd	*next;
} t_cmd;

// structs para o lexer
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
}	t_token_type;

typedef struct s_token
{
    char			*value;
    t_token_type	type;
    struct s_token	*next;
}	t_token;

// - ------------ -- --- Para o parser

typedef enum e_node_type
{
    N_PIPE,
    N_AND,
    N_OR,
    N_CMD
}	t_node_type;

typedef struct s_simple_cmd
{
    char	**args;
    t_list	*redir_list; // Use libft list for redirections
}	t_simple_cmd;

// This is the main AST node
typedef struct s_node
{
    t_node_type		type;
    t_simple_cmd	*simple_cmd; // Only used if type is N_CMD
    struct s_node	*left;
    struct s_node	*right;
}	t_node;
// ------------------------------------

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
** srcs/utils/split.c
*/
char	**shell_split(char const *s);
void	free_str_array(char **arr);
void	free_str(char **str);

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
** srcs/env/env.c
*/
t_env	*init_env(char **envp);
char	**convert_env_to_array(t_env *env_list);
t_env	*find_env_node(t_env *env_list, const char *key);
void	add_env_node_back(t_env **env_list_head, t_env *new_node);
t_env	*new_env_node(char *key, char *value);
void	free_env_node(t_env *node);
void	free_env_list(t_env *head);

/*
** srcs/env/env_utils.c
*/
void	bubble_sort_array(char **arr);
void	set_env_var(t_shell *shell, const char *key, const char *value);
char	*get_env_value(t_shell *shell, const char *key);
int		is_valid_identifier(const char *str);

/*
** srcs/lexer/lexer.c
*/
t_token	*lexer(char const *s);
void	ft_clear_token_list(t_token **list);
int		is_separator_char(char c);
void	skip_whitespace(const char *s, size_t *i);
int		is_quote(char c);
bool	ft_skip_quotes(const char *line, size_t *i);
void	ft_print_quote_err(char c);

/*
** srcs/parser/parser.c
*/
t_cmd	*parser(char *line, t_shell *shell);
t_cmd	*parse_tokens(t_token *tokens, t_shell *shell);
t_cmd	*new_cmd_node(char *cmd, char **flags);
void	add_cmd_node_back(t_cmd **cmd_list_head, t_cmd *new_node);
void	free_cmds(t_cmd *cmd_list);
int		check_syntax(t_token *tokens, t_shell *shell);
int		count_args(t_token *tokens);
int		print_syn_error(char *str, t_shell *shell);
int		is_redir_token(t_token_type t);
t_token	*get_last_token(t_token *token_list);

/*
** srcs/heredoc/heredoc.c
*/
int		handle_heredoc(const char *delimiter, int expand, t_shell *shell);

/*
** srcs/expansion/expand.c
*/
void	expand_variables(t_cmd *cmd, t_shell *shell);
char	*expand_line_for_heredoc(char *line, t_shell *shell);

/*
** srcs/exec/exec.c
*/
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2]);
void	execute_command(char **args, char *envp[]);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		exe_builtin(char **args, t_shell *shell);

/*
** srcs/builtins/
*/
int		echo_builtin(char **args, t_shell *shell);
int		ft_cd(char **args, t_shell *shell);
int		pwd_builtin(t_shell *shell);
int		exit_builtin(char **args, t_shell *shell);
int		env_builtin(t_shell *shell);
void	print_sorted_env(t_shell *shell);
int		unset_builtin(char **args, t_shell *shell);
int		export_builtin(char **args, t_shell *shell);
int		is_builtin(char **args);
char	*get_target_path(char **args, t_shell *shell);

#endif