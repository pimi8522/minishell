/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:42:53 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/26 17:18:54 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_cwd(char *buf, size_t size)
{
    if (getcwd(buf, size) == NULL)
    {
        perror(RED"getcwd"RST);
        exit(EXIT_FAILURE);
    }
    return (buf);
}

void *do_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED"malloc"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void print_banner(void)
{
    printf(
        C
        "┏┳┓╻┏┓╻╻┏━┓╻ ╻┏━╸╻  ╻     ┏━┓╻ ╻┏━╸╻┏ ┏━┓\n"
        "┃┃┃┃┃┗┫┃┗━┓┣━┫┣╸ ┃  ┃     ┗━┓┃ ┃┃  ┣┻┓┗━┓\n"
        "╹ ╹╹╹ ╹╹┗━┛╹ ╹┗━╸┗━╸┗━╸   ┗━┛┗━┛┗━╸╹ ╹┗━┛\n"
        RST);
}

void	set_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		node = new_env_node(ft_strdup(key), ft_strdup(value));
		if(node)
			add_env_node_back(env_list, node);
	}
	
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*node;

	node = find_env_node(env_list, key);
	if (node)
		return(node->value);
	return (NULL);
}

void	expand_variables(t_cmd *cmd, t_env *env_list)
{
	int		i;
	char	*status_str;

	if(!cmd || !cmd->flag)
		return ;
	status_str = get_env_value(env_list, "?");
	if(!status_str)
		status_str = "0";
	i = 0;
	while(cmd->flag[i])
	{
		if(ft_strcmp(cmd->flag[i], "$?") == 0)
		{
			free(cmd->flag[i]);
			cmd->flag[i] = ft_strdup(status_str);
		}
		i++;
	}
}