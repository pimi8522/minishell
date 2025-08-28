/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:37 by adores            #+#    #+#             */
/*   Updated: 2025/08/12 12:26:30 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	call_child1(char **av, char **envp, int *fd)
{
	int	file1;

	file1 = open(av[1], O_RDONLY);
	if (file1 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_all_files(fd, file1);
	exec(av[2], envp);
}

static void	call_child2(char **av, char **envp, int *fd)
{
	int	file2;

	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_error();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close_all_files(fd, file2);
	exec(av[3], envp);
}

static int	ft_wait(pid_t *proc_id)
{
	int	exit_code;
	int	status;

	exit_code = 0;
	if (waitpid(proc_id[1], &status, 0) < 0)
		ft_error();
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (waitpid(proc_id[0], NULL, 0) < 0)
		ft_error();
	return (exit_code);
}

static void	pipex_process(char **av, char *envp[], pid_t proc_id[2])
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_error();
	proc_id[0] = fork();
	if (proc_id[0] < 0)
		close_and_error(fd);
	if (proc_id[0] == 0)
		call_child1(av, envp, fd);
	else
	{
		proc_id[1] = fork();
		if (proc_id[1] < 0)
			close_and_error(fd);
		if (proc_id[1] == 0)
			call_child2(av, envp, fd);
	}
	if (close(fd[0]) < 0 || close(fd[1]) < 0)
		ft_error();
}

int	main(int ac, char **av, char *envp[])
{
	pid_t	proc_id[2];
	int		exit_code;

	exit_code = 0;
	if (ac == 5)
	{
		pipex_process(av, envp, proc_id);
		exit_code = ft_wait(proc_id);
	}
	else
	{
		write(2, "ERROR: Number of arguments should be five.", 42);
		return (1);
	}
	return (exit_code);
}
