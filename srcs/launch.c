/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:39:56 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/16 15:15:48 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_single_command(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		printf("Execute single command: %s...\n", args[0]);
		execute_command(args, envp);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell: fork error");
	else
	{
		waitpid(pid, &status, 0);
	}
}

static void execute_pipe_command(char **cmd1, char **cmd2, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	printf("Executing pipe command: %s | %s..\n", cmd1[0], cmd2[0]);
	if(pipe(fd) == -1)
	{
		perror("minishell: pipe error");
		return;
	}
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_command(cmd1, envp);
	}
	pid2 = fork();
	if(pid2 < 0)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_command(cmd2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
}

static int	find_pipe_index(char **args)
{
	int i;
	i = 0;
	while(args && args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return(i);
		i++;
	}
	return(-1);
}



void shell_launch(char **args, char **envp)
{
	int pipe_index;
	char **cmd1;
	char **cmd2;
	if(!args || !args[0])
	{
		//exit?
		return ;
	}
	if(exe_builtin(args, ))
		return;
	pipe_index = find_pipe_index(args);
	if (pipe_index != -1)
	{
		args[pipe_index] = NULL;
		cmd1 = args;
		cmd2 = &args[pipe_index + 1];
		if (!cmd2[0])
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			return ;
		}
		execute_pipe_command(cmd1, cmd2, envp);
	}
	else
		execute_single_command(args, envp);
}
/* void	shell_launch(char **args)
{
	// Is fork returning 2 values?
	if (Fork() == 0)
	{
		// replace the current process image with a new process image
		//v for "vector", p for "path".
		//Takes an array of arguments and uses PATH to find the executable.
		//	char *args[] = {"ls", "-l", "-a", NULL};
		//	execve("ls", args);
		execve(args[0], args);
	}
	else
	{
		//Automatically waits for any child process, 
		//which is often sufficient for beginner-level 
		//shells that only handle one child process at a time.
		// FINE for SHELL v°1
		//Wait(&status);
		waitpid(cell_jr, &status, 0);

	}
} */


/* void	forkado(t_list *list)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		executor(list);
	}
	
} */

/* void shell_exec(char **args)
{
	int			i;
	const char	*curr_builtin;

	if (!args || !args[0])
		return ;
	i = 0;

    //if is builtin
        //run builtin
	
	// fork and launch 
	shell_launch(args);
} */