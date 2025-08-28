/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:09:08 by adores            #+#    #+#             */
/*   Updated: 2025/08/12 11:19:15 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "libft/libft.h"

void	ft_error(void);
void	cmd_not_found(void);
void	exec(char *av, char *envp[]);
void	close_all_files(int *fd, int file);
void	close_and_error(int *fd);