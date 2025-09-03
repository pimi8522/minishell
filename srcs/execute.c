/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:30:19 by anarita           #+#    #+#             */
/*   Updated: 2025/09/03 14:51:20 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
		free(str[--i]);
	free(str);
}

static char	*get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*add_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		add_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(add_path, &cmd[0]);
		free(add_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_str(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_str(paths);
	return (NULL);
}

static char	*find_path(char *envp[], char *cmd)
{
	char	**paths;
	int		i;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!envp || !*envp)
		ft_error();
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		ft_error(); //nao e suposto dar error com certas funcoes
	path = get_cmd_path(paths, cmd);
	return (path);
}

void	execute_command(char **args, char *envp[])
{
	char	*path;
	path = find_path(envp, args[0]);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(path, args, envp);
	free(path);
	perror("minishell");
	exit(EXIT_FAILURE);
}
