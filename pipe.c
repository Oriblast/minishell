/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:44:23 by mounali           #+#    #+#             */
/*   Updated: 2023/10/05 21:05:52 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_process(char **args, char *full_cmd_path, char **env)
{
	if (execve(full_cmd_path, args, env) == -1)
	{
		perror("execve");
		free(full_cmd_path);
		exit(1);
	}
}

void	child_processes(char *cmd, int *read_fd, int *write_fd, char **env)
{
	char	**args;
	char	*full_cmd_path;

	if (read_fd)
		dup2(*read_fd, 0);
	if (write_fd)
		dup2(*write_fd, 1);
	if (read_fd)
		close(*read_fd);
	if (write_fd)
		close(*write_fd);
	args = ft_split(cmd, ' ');
	full_cmd_path = find_cmd_in_path(args[0], env);
	if (!full_cmd_path)
		perror("command not found");
	else
		fork_process(args, full_cmd_path, env);
	exit(1);
}

void	execute_single_command_in_pipe(char *cmd, int *read_fd,
	int *write_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		child_processes(cmd, read_fd, write_fd, env);
	else
		g_child_pid = pid;
}

void	initialize_pipes(int num_cmds, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * (num_cmds - 1));
	i = -1;
	while (++i < num_cmds - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (pipe((*pipes)[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}
