/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:01:08 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 21:01:16 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prepare_args(t_command *cmd, char **envp)
{
	char	**args;

	args = construct_args_for_execve(cmd, envp, 1);
	return (args);
}

char	*get_command_path(t_command *cmd, char **envp)
{
	if (strncmp(cmd->cmd_name, "/", 1) == 0)
		return (strdup(cmd->cmd_name));
	return (find_cmd_in_path(cmd->cmd_name, envp));
}
