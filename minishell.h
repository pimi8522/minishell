/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarita <anarita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:51 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/01 11:32:39 by anarita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>
#include <fcntl.h>
#include <time.h>

# include "libft/libft.h"

#define SPACE	"\t\n\v\f\r "


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

char *get_cwd(char *buf, size_t size);
void *do_malloc(size_t size);
void print_banner(void);
char **shell_split(char const *s);
void shell_launch(char **args);

#endif