/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:11:04 by mounali           #+#    #+#             */
/*   Updated: 2023/10/01 20:11:16 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_extern_cmd(char *cmd, char **args, char **envp, int should_fork)
{
	pid_t	pid;

	if (should_fork)
	{
		pid = fork();
		execute_helper(pid, cmd, args, envp);
	}
	else
	{
		if (execve(cmd, args, envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
}
