/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:04 by adores & mi       #+#    #+#             */
/*   Updated: 2025/09/19 16:35:58 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	if(!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static void	echo_builtin(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
			printf(" ");
		i++;
	}
	if(newline == 1)
		printf("\n");
}

void	ft_cd(char **args)
{
	if(!args[1])
	{
		write(2, "minishell: cd: missing argument\n", 31);
		return ;
	}
	if(chdir(args[1]) != 0)
		perror("minishell: cd");
}

static void pwd_builtin(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
		perror("pwd");
}

static void	exit_builtin(char **args)
{
	int	exit_code;

	if(!args[1])
		exit(0);
	exit_code = ft_atoi(args[1]);
	if(args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ; // We should set a specific error status here, but for now, just return.
	}
	exit(exit_code);
}

static void	env_builtin(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

static void	unset_builtin(char **args, t_env **env_list_head)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		current = *env_list_head;
		prev = NULL;
		while(current)
		{
			if(ft_strcmp(current->key, args[i]) == 0)
			{
				if (prev == NULL)
					*env_list_head = current->next;
				else
					prev->next = current->next;
				free_env_node(current);
				break;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}

static void	print_sorted_env(t_env *env_list)
{
	char	**env_array;
	int		i;
	char	*equal_sign;
	char	*key;

	env_array = convert_env_to_array(env_list);
	if (!env_array)
		return;
	bubble_sort_array(env_array);
	i = 0;
	while(env_array[i])
	{
		equal_sign = ft_strchr(env_array[i], '=');
		if (equal_sign)
		{
			key = ft_substr(env_array[i], 0, equal_sign - env_array[i]);
			if (key)
			{
				printf("declare -x %s=\"%s\"\n", key, equal_sign + 1);
				free(key);
			}
		}
		else
			printf("declare -x %s\n", env_array[i]);
		i++;
	}
	free_str(env_array);
}

static void	export_builtin(char **args, t_env **env_list_head)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*existing_node;
	t_env	*new_node;

	i = 1;
	if (!args[i])
	{
		print_sorted_env(*env_list_head);
		return ;
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			if(!key)
				break;
			value = ft_strdup(equal_sign + 1);
			if(!value)
			{
				free(key);
				break;
			}
			existing_node = find_env_node(*env_list_head, key);
			if(existing_node)
			{
				free(existing_node->value);
				existing_node->value = value;
				free(key);
			}
			else
			{
				new_node = new_env_node(key, value);
				if (!new_node)
				{
					free(key);
					free(value);
					break;
				}
				add_env_node_back(env_list_head, new_node);
			}
		}
		i++;
	}
}

int	exe_builtin(char **args, t_env **env_list)
{
	if(!args || !args[0])
		return(0);
	if(ft_strcmp(args[0], "echo") == 0)
	{
		echo_builtin(args);
		return(1);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(args);
		return (1) ;
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		pwd_builtin();
		return(1);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		exit_builtin(args);
		return(1);
	}
	else if(ft_strcmp(args[0], "env") == 0)
	{
		env_builtin(*env_list);
		return(1);
	}
	else if(ft_strcmp(args[0], "unset") == 0)
	{
		unset_builtin(args, env_list);
		return(1);
	}
	else if(ft_strcmp(args[0], "export") == 0)
	{
		export_builtin(args, env_list);
		return(1);
	}
	return(0);
}
