/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:13:52 by adores            #+#    #+#             */
/*   Updated: 2025/05/09 14:38:08 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	while (*buffer || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoingnl(line, buffer);
		if (ft_bufferreset(buffer))
			break ;
	}
	return (line);
}

/* #include <stdio.h>
int main()
{
	char *gnl_fd;
	int fd = open("test.txt", O_RDONLY | O_CREAT);
	while ((gnl_fd = get_next_line(fd)) != NULL)
	{
		printf("%s", gnl_fd);
		free(gnl_fd);	
	}
	printf("\n");
	close(fd);
} */
/* HelloWorld
GetNext
Line

buffer_size = 2

line = NULL
buffer = He

line = He


line = He
buffer = ll

line = Hell */