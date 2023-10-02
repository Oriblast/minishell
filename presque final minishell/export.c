/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:04:21 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 21:58:54 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_env(char *name, char **envp)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *name, char *value, char **envp, int index)
{
	if (!name || !value)
		return ;
	free(envp[index]);
	envp[index] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!envp[index])
	{
		perror("Erreur d'allocation mémoire");
		return ;
	}
	ft_strcpy(envp[index], name);
	ft_strcat(envp[index], "=");
	ft_strcat(envp[index], value);
}

char	*joindrelesdeux_bouts(char *name, char *value)
{
	char	*str;
	int		len;

	if (!name || !value)
		return (NULL);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strcpy(str, name);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

void	add_new_env(char *name, char *value, char ***envp_ref)
{
	char	**new_env;
	char	**envp;
	int		len;
	int		i;

	envp = *envp_ref;
	len = 0;
	while (envp[len])
		len++;
	new_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return ;
	i = -1;
	while (envp[++i])
		new_env[i] = envp[i];
	new_env[len] = joindrelesdeux_bouts(name, value);
	new_env[len + 1] = NULL;
	*envp_ref = new_env;
}

char	**export_cmd(char *command, char ***envp)
{
	char	*equal_sign;
	char	name[5000];
	int		index;

	equal_sign = ft_strchr(command, '=');
	if (!equal_sign)
	{
		printf("export: format invalid. Expected format: NAME=VALUE\n");
		return (NULL);
	}
	ft_strncpy(name, command, equal_sign - command);
	name[equal_sign - command] = '\0';
	index = index_env(name, *envp);
	if (index != -1)
		update_env(name, equal_sign + 1, *envp, index);
	else
		add_new_env(name, equal_sign + 1, envp);
	return (*envp);
}
