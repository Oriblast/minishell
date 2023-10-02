/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:08:41 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 21:57:47 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*get_env_value(char *key, char **envp)
{
	int		i;
	int		key_len;

	i = 0;
	key_len = strlen(key);
	while (envp[i])
	{
		if (!strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
			return (&envp[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

void	handle_var_substitution(char *line, int *i, char **envp)
{
	int		var_len;
	int		end;
	char	var_key[255];
	char	*value;

	end = (*i) + 1;
	while (line[end] && (isalnum(line[end]) || line[end] == '_'))
		end++;
	var_len = end - (*i) - 1;
	strncpy(var_key, &line[(*i) + 1], var_len);
	var_key[var_len] = '\0';
	value = get_env_value(var_key, envp);
	if (value)
		write(1, value, strlen(value));
	*i = end;
}

void	print_between_quotes(char *line, int *i, char **envp)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '$')
			handle_var_substitution(line, i, envp);
		else
			ft_putchar_fd(line[(*i)++], 1);
	}
}

int	parse_echo_flags(char *line, int *i)
{
	if (!strncmp(line + *i, "-n", 2) && isspace(line[*i + 2]))
	{
		*i += 3;
		return (0);
	}
	return (1);
}
