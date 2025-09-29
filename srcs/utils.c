/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:42:53 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/29 15:58:34 by adores & mi      ###   ########.fr       */
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

char	*str_append_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if(str)
		len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if(!new_str)
		return (NULL);
	if(str)
		ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if(str)
		free(str);
	return(new_str);
}

char	*extract_var_name(const char *str)
{
	int	i;

	i = 0;
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return(ft_substr(str, 0, i));
}

char	*expand_arg(char *arg, t_env *env_list)
{
	char	*new_arg;
	int		i;
	char	*var_name;
	char	*var_value;
	char	*temp;

	new_arg = ft_strdup("");
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '$')
		{
			var_name = extract_var_name(&arg[i + 1]);
			var_value = get_env_value(env_list, var_name);
			i += ft_strlen(var_name) + 1;
			if (var_value)
			{
				temp = ft_strjoin(new_arg, var_value);
				free(new_arg);
				new_arg = temp;
			}
			free(var_name);
		}
		else
			new_arg = str_append_char(new_arg, arg[i++]);
	}
	free(arg);
	return(new_arg);
}

void	expand_variables(t_cmd *cmd, t_env *env_list)
{
	int		i;
	
	if(!cmd || !cmd->flag)
		return ;
	i = 0;
	while(cmd->flag[i])
	{
		if(ft_strchr(cmd->flag[i], '$'))
			cmd->flag[i] = expand_arg(cmd->flag[i], env_list);
		i++;
	}
}