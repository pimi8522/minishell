/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/16 13:14:03 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_history_path(void)
{
	char	*home;
	char	*history_path;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	history_path = ft_strjoin(home, "/.minishell_history");
	return (history_path);
}

static void	load_history_from_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (*line)
			add_history(line);
		free(line);
		line = get_next_line(fd);
	}
}

int	init_shell_history(void)
{
	char	*history_path;
	int		fd;

	history_path = get_history_path();
	if (!history_path)
		return (-1);
	fd = open(history_path, O_RDONLY);
	free(history_path);
	if (fd < 0)
		return (-1);
	load_history_from_fd(fd);
	close(fd);
	return (0);
}

static void	write_history_to_fd(int fd)
{
	int			i;
	HIST_ENTRY	*entry;

	i = 1;
	entry = history_get(i);
	while (entry != NULL)
	{
		if (entry->line)
		{
			write(fd, entry->line, ft_strlen(entry->line));
			write(fd, "\n", 1);
		}
		i++;
		entry = history_get(i);
	}
}

void	save_shell_history(void)
{
	char	*history_path;
	int		fd;

	history_path = get_history_path();
	if (!history_path)
		return ;
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(history_path);
	if (fd < 0)
		return ;
	write_history_to_fd(fd);
	close(fd);
}
