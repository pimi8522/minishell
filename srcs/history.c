/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/10/10 17:05:12 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comandos ficam guardados em minishell.history
int	init_shell_history(void)
{
	char	*home;
	char	*history_path;
	int		fd;
	char	*line;

	home = getenv("HOME");
	if (!home)
		return (-1);
	history_path = ft_strjoin(home, "/.minishell_history");
	if (!history_path)
		return (-1);
	fd = open(history_path, O_RDONLY);
	free(history_path);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (*line)
			add_history(line);
		free(line);
	}
	close(fd);
	return (0);
}

//guardar no actual ficheiro
void	save_shell_history(void)
{
	char		*home;
	char		*history_path;
	int			fd;
	int			i;
	HIST_ENTRY	*entry;

	i = 1; //history starts at index 1
// obter o diretório home do utilizador
	home = getenv("HOME");
	if (!home)
		return ;
// construir o caminho para o ficheiro de histórico
	history_path = ft_strjoin(home, "/.minishell_history");
	if (!history_path)
		return ;
	
// abrir/criar o ficheiro para escrita, apagando o conteúdo anterior
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(history_path);
	if (fd < 0)
		return ;
	

//escrever cada entrada do historico no ficheiro	
	while ((entry = history_get(i)) != NULL)
	{
		if (entry->line)
		{
			write(fd, entry->line, ft_strlen(entry->line));
			write(fd, "\n", 1);
		}
		i++;
	}
	
// Fechar o file descriptor
	close(fd);
}
