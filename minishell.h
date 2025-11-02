/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/31 15:31:12 by adores & mi      ###   ########.fr       */
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
# include "pipex/pipex.h"
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



//structs para o shell split line
typedef struct s_tokbuf {
	char   *buf;
	size_t  len;
	size_t  cap;
}   t_tokbuf;

typedef struct s_split {
	const char *s;
	size_t      i;
	int         in_squote;
	int         in_dquote;
	char      **tokens;
	size_t      tcount;
	size_t      tcap;
	t_tokbuf    tok;
}   t_split;


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


char	*get_cwd(char *buf, size_t size);
void	*do_malloc(size_t size);
void	print_banner(void);
char	**shell_split(char const *s);

void	execute_command(char **args, char *envp[]);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
void	execute_child(t_cmd *cmd, t_shell *shell, int input_fd, int pipe_fds[2]);
int		exe_builtin(char **args, t_shell *shell);
void	sigint_handler(int signo);
void	setup_interactive_signals(void);
void	setup_exec_signals(void);
void	heredoc_sigint_handler(int signo);
int		init_shell_history(void);
void	save_shell_history(void);
t_env	*init_env(char **envp);
char	**convert_env_to_array(t_env *env_list);
t_env	*find_env_node(t_env *env_list, const char *key);
void	add_env_node_back(t_env **env_list_head, t_env *new_node);
t_env	*new_env_node(char *key, char *value);
void	bubble_sort_array(char **arr);
void	free_str(char **str);
void	free_env_node(t_env *node);
t_cmd	*parse_line(char *line, t_shell *shell);
void	free_cmds(t_cmd *cmd_list);
t_cmd	*new_cmd_node(char *cmd, char **flags);
void	add_cmd_node_back(t_cmd **cmd_list_head, t_cmd *new_node);
int		handle_heredoc(const char *delimiter, int expand, t_shell *shell);

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

void	set_env_var(t_shell *shell, const char *key, const char *value);
char	*get_env_value(t_shell *shell, const char *key);
void	expand_variables(t_cmd *cmd, t_shell *shell);
char	*expand_line_for_heredoc(char *line, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
int		is_valid_identifier(const char *str);
#endif