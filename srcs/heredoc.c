#include "../minishell.h"

static void	read_heredoc(const char *delimiter, int fd, int expand,
		t_shell *shell)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (expand)
		{
			expanded_line = expand_line_for_heredoc(line, shell);
			ft_putendl_fd(expanded_line, fd);
			free(expanded_line);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(const char *delimiter, int expand, t_shell *shell)
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
		signal(SIGINT, heredoc_sigint_handler);
		close(pipe_fd[0]);
		read_heredoc(delimiter, pipe_fd[1], expand, shell);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->last_exit_status = 130;
		close(pipe_fd[0]);
		write(1, "\n", 1);
		return (-1);
	}
	return (pipe_fd[0]);
}