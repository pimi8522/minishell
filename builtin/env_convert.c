/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:30:29 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/20 11:30:29 by adores & mi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_nodes(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static char *make_env_entry(t_env *node)
{
	char 	*temp;
	char	*entry;

	if (node->value)
	{
		temp = ft_strjoin(node->key, "=");
		entry = ft_strjoin(temp, node->value);
		free(temp);
	}
	else
		entry = ft_strdup(node->key);
	return (entry);
}

char	**convert_env_to_array(t_env *env_list)
{
	char	**env_array;
	int		count;
	int		i;

	count = count_env_nodes(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if(!env_array)
		return(NULL);
	i = 0;
	while(env_list)
	{
		env_array[i++] = make_env_entry(env_list);
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return(env_array);
}


static int	count_array_strings(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return(0);
	while (arr[count])
		count++;
	return(count);
}
