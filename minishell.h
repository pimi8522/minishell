/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/17 15:15:21 by adores & mi      ###   ########.fr       */
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
# include <limits.h>

# include "libft/libft.h"
# include "pipex/pipex.h"

#define WHITESPACE	"\t\n\v\f\r "


typedef struct s_cmd
{
	char	*cmd;
	char	**flag;
	int		in;
	int		out;
	int		fd[2];
	/* data */
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

/*
** ANSI Color codes for terminal output formatting:
** Y    - Yellow
** G    - Green
** C    - Cyan
** RED  - Red
** RST  - Reset to default color
*/
#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST 	"\033[0m"

char	*get_cwd(char *buf, size_t size);
void	*do_malloc(size_t size);
void	print_banner(void);
char	**shell_split(char const *s);
void	shell_launch(char **args, t_env *env_list);
void	execute_command(char **args, char *envp[]);
int		exe_builtin(char **args, t_env *env_list);
void	sigint_handler(int signo);
int		init_shell_history(void);
void	save_shell_history(void);
t_env	*init_env(char **envp);
char	**convert_env_to_array(t_env *env_list);

#endif