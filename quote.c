/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:15:44 by ksongbe           #+#    #+#             */
/*   Updated: 2023/09/23 21:15:48 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	child_process(char *cmd, char **env)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	execve(args[0], args, env);
	perror("execve");
	free_str_array(args);
	exit(EXIT_FAILURE);
}

int	quote(char *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
		child_process(cmd, env);
	else
		waitpid(pid, &status, 0);
	return (1);
}
