#include "../minishell.h"

static void	read_heredoc(const char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		read_heredoc(delimiter, pipe_fd[1]);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	return (pipe_fd[0]);
}