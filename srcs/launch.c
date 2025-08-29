/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:39:56 by miduarte &        #+#    #+#             */
/*   Updated: 2025/08/29 14:40:02 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shell_launch(char **args)
{
    (void)args;
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