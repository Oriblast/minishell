/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:34:37 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 17:34:39 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

char	*get_path_from_envp(char **envp)
{
	int		i;
	char	*prefix;

	i = 0;
	prefix = "PATH=";
	while (envp[i])
	{
		if (ft_strncmp(envp[i], prefix, 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	execute_cmd_with_path(char *cmd, char **args, char **envp)
{
	char	*full_cmd;

	full_cmd = find_cmd_in_path(cmd, envp);
	if (full_cmd)
	{
		execve(full_cmd, args, envp);
		free(full_cmd);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
}
