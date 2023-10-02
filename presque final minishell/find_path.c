/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:14:11 by mounali           #+#    #+#             */
/*   Updated: 2023/10/02 20:14:33 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

char	*check_command_path(char **paths, char *cmd)
{
	struct stat	st;
	int			i;
	char		*full_cmd;

	i = 0;
	while (paths[i])
	{
		full_cmd = ft_strjoin(paths[i], cmd);
		if (!full_cmd)
			break ;
		if (stat(full_cmd, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free_str_array(paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

char	*find_cmd_in_path(char *cmd, char **envp)
{
	char		*path;
	char		**paths;
	struct stat	st;

	if (cmd && cmd[0] == '/' && stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
		return (ft_strdup(cmd));
	path = get_path_from_envp(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (check_command_path(paths, cmd));
}
