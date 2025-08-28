/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:29:06 by adores            #+#    #+#             */
/*   Updated: 2025/08/12 12:23:37 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_error();
	path = get_cmd_path(paths, cmd);
	return (path);
}

void	exec(char *av, char *envp[])
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free(cmd);
		cmd_not_found();
	}
	path = find_path(envp, cmd[0]);
	if (!path)
	{
		free_str(cmd);
		perror(av);
		exit(127);
	}
	free(cmd[0]);
	cmd[0] = path;
	if (path == cmd[0] && !ft_strchr(cmd[0], '/'))
		ft_error();
	if (execve(cmd[0], cmd, envp) == -1)
	{
		free_str(cmd);
		ft_error();
	}
}
