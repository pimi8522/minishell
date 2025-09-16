/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:06:45 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/16 16:12:27 by miduarte &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comandos ficam guardados em minishell.history
int	init_shell_history(void)
{
	char	*home;
	char	*history_path;
	int		fd;
	char	buffer[4096];
	ssize_t	bytes_read;
	char	*line_start;
	char	*newline;

// obter o diretório home do utilizador
	home = getenv("HOME");
	if (!home)
		return (-1);
// construir o caminho para o ficheiro de histórico
	history_path = ft_strjoin(home, "/.minishell_history");
	if (!history_path)
		return (-1);
		
// abrir o ficheiro de histórico para leitura
	fd = open(history_path, O_RDONLY);
	free(history_path);
	if (fd < 0)
		return (-1);
	
// ler o conteúdo do ficheiro para um buffer
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		close(fd);
		return (bytes_read < 0 ? -1 : 0);
	}
	
	buffer[bytes_read] = '\0';
	line_start = buffer;
	
// processar o buffer linha por linha, adicionando cada uma ao histórico
	while ((newline = ft_strchr(line_start, '\n')))
	{
		*newline = '\0';
		if (*line_start)  /* Skip empty lines */
			add_history(line_start);
		line_start = newline + 1;
	}
	
//adicionar a ultima linha se n acabar em newline
	if (*line_start)
		add_history(line_start);
	
//fechar o file descriptor
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
