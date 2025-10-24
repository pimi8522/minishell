/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:28:44 by adores & mi       #+#    #+#             */
/*   Updated: 2025/10/01 18:41:00 by Roo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adiciona um caractere a uma string, realocando a memória
static char	*str_append_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if (str)
		free(str);
	return (new_str);
}

// extrai o nome da variável de uma string (ex: de $USER, extrai USER)
static char	*extract_var_name(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?' || str[i] == '$')
		return (ft_substr(str, 0, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

// obtém o valor da variável de ambiente e anexa-o à string
static char	*append_var_value(char *current_str, char *var_name, t_shell *shell)
{
	char	*var_value;
	char	*new_str;

	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(shell->last_exit_status);
	else if (ft_strcmp(var_name, "$") == 0)
		var_value = ft_itoa(shell->pid);
	else
		var_value = get_env_value(shell, var_name);
	if (var_value)
	{
		new_str = ft_strjoin(current_str, var_value);
		if (ft_strcmp(var_name, "?") == 0 || ft_strcmp(var_name, "$") == 0)
			free(var_value);
	}
	else
		new_str = ft_strdup(current_str);
	free(current_str);
	return (new_str);
}

char	*expand_tilde(char *arg, t_shell *shell)
{
	char	*home;
	char	*result;

	if (!arg || arg[0] != '~')
		return (arg);
	home = get_env_value(shell, "HOME");
	if (!home)
		return (arg);
	if (arg[1] == '\0')
	{
		free(arg);
		return (ft_strdup(home));
	}
	if (arg[1] == '/')
	{
		result = ft_strjoin(home, arg + 1);
		free(arg);
		return (result);
	}
	return(arg);
}

// função principal que expande variáveis e remove aspas de um argumento
static char	*expand_and_unquote_arg(char *arg, t_shell *shell)
{
	char	*new_arg;
	int		i;
	int		in_squote;
	int		in_dquote;
	char	*var_name;

	new_arg = ft_strdup("");
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (arg[i])
	{
		// se for uma plica e não estiver dentro de aspas, muda o estado de in_squote
		if (arg[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
		}
		// se for aspas e não estiver dentro de plicas, muda o estado de in_dquote
		else if (arg[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		// se for um '$' e não estiver dentro de plicas, expande a variável
		else if (arg[i] == '$' && !in_squote)
		{
			if(arg[i + 1] == '"')
			{
				i++;
				continue;
			}
			if (!ft_isalnum(arg[i + 1]) && arg[i + 1] != '_' 
				&& arg[i + 1] != '?' && arg[i + 1] != '$')
			{
				// Not a valid variable, treat $ as literal
				new_arg = str_append_char(new_arg, arg[i]);
				i++;
			}
			else
			{
				var_name = extract_var_name(&arg[i + 1]);
				new_arg = append_var_value(new_arg, var_name, shell);
				if (ft_strcmp(var_name, "$") == 0)
					i += 2;
				else
					i += ft_strlen(var_name) + 1;
				free(var_name);
			}
		}
		else
		{
			// senão, apenas adiciona o caractere ao novo argumento
			new_arg = str_append_char(new_arg, arg[i]);
			i++;
		}
	}
	free(arg);
	return (new_arg);
}

// itera sobre os argumentos de um comando e expande cada um
void	expand_variables(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->flag)
		return ;
	i = 0;
	while (cmd->flag[i])
	{
		cmd->flag[i] = expand_tilde(cmd->flag[i], shell);
		if (ft_strchr(cmd->flag[i], '$') || ft_strchr(cmd->flag[i], '\'')
			|| ft_strchr(cmd->flag[i], '"'))
		{
			cmd->flag[i] = expand_and_unquote_arg(cmd->flag[i], shell);
		}
		i++;
	}
}

char	*expand_line_for_heredoc(char *line, t_shell *shell)
{
	char	*new_line;
	int		i;

	new_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!ft_isalnum(line[i + 1]) && line[i + 1] != '_'
				&& line[i + 1] != '?'&& line[i + 1] != '$')
			{
				new_line = str_append_char(new_line, line[i]);
				i++;
			}
			else
			{
				char *var_name = extract_var_name(&line[i + 1]);
				new_line = append_var_value(new_line, var_name, shell);
				i += ft_strlen(var_name) + 1;
				free(var_name);
			}
		}
		else
		{
			new_line = str_append_char(new_line, line[i]);
			i++;
		}
	}
	return (new_line);
}
