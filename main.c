/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:19:30 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/28 12:01:56 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **split_line(char *line)
{
    char **tokens;

    tokens = ft_split(line, SPACE); //TODO: find a way to get whitespace
    return tokens;
}

void	shell_launch(char **args)
{
	// Is fork returning 2 values?
	if (Fork() == SHELL_JR)
	{
		// replace the current process image with a new process image
		//v for "vector", p for "path".
		//Takes an array of arguments and uses PATH to find the executable.
		//	char *args[] = {"ls", "-l", "-a", NULL};
		//	execvp("ls", args);
		Execvp(args[0], args);
	}
	else
	{
		//Automatically waits for any child process, 
		//which is often sufficient for beginner-level 
		//shells that only handle one child process at a time.
		// FINE for SHELL v°1
		//Wait(&status);
		/*
		Waitpid(cell_jr, &status, 0);
		*/
	}
}

void shell_exec(char **args)
