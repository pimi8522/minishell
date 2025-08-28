/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:19:30 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/28 12:03:05 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **split_line(char *line)
{
    char **tokens;

    tokens = ft_split(line, ' ');
    return tokens;
}

/* void	shell_launch(char **args)
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
		Waitpid(cell_jr, &status, 0);

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

char *read_line(void)
{
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];

    buf = NULL;
    get_cwd(cwd, sizeof(cwd));
    ft_printf(RED"%s "RST, cwd);
    ft_printf(""C"minishell$ "RST);
    if (getline(&buf, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            ft_printf(RED"EOF\n"RST);
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror(RED"readline"RST);
            exit(EXIT_FAILURE);
        }
    }
    return (buf);
    
}

int main (int ac, char **av)
{
    char *line;
    char **args;
    int i;

    (void)ac;
    (void)av;
    i = 0;
    print_banner();
    while((line = read_line()))
    {   
        args = split_line(line);
        while(args[i])
        {
           ft_printf("You entered: %s\n", args[i]);
           i++;
        }
    }
    free(line);
    free(args);
    return EXIT_SUCCESS;
}
