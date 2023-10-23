/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:10:24 by mounali           #+#    #+#             */
/*   Updated: 2023/10/23 22:58:58 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipelines(t_command **commands, char **envp)
{
	int		num_cmds;
	int		pipe_fds[10][2];
	int		i;
	pid_t	pid;

	num_cmds = count_commands(commands);
	create_pipes(num_cmds, pipe_fds);
	i = -1;
	while (++i < num_cmds)
	{
		pid = fork();
		if (pid == -1)
			perror("minishell: fork error");
		else if (pid == 0)
			setup_child_process(i, num_cmds, pipe_fds, commands, envp);
	}
	close_pipes_and_wait(num_cmds, pipe_fds);
}

void	free_subcommands(t_subcommand **subcommands)
{
	int	i;

	if (!subcommands)
		return ;
	i = 0;
	while (subcommands[i])
	{
		free(subcommands[i]->cmd_name);
		free(subcommands[i]);
		i++;
	}
	free(subcommands);
}

char	*trim(char *str)
{
	char	*end_str;

	if (!str)
		return (NULL);
	while (isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end_str = str + strlen(str) - 1;
	while (end_str > str && isspace((unsigned char)*end_str))
		end_str--;
	end_str[1] = '\0';
	return (str);
}

void	setup_child_process(int i, int num_cmds, int pipe_fds[][2],
		t_command **commands, char **envp)
{
	char	**args;
	char	*full_cmd_path;

	if (i != 0)
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
	if (i != num_cmds - 1)
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	close_pipes(num_cmds, pipe_fds);
	handle_redirections(commands[i]);
	args = construct_args_for_execve(commands[i], envp, 0);
	full_cmd_path = find_cmd_in_path(commands[i]->cmd_name, envp);
	execve(full_cmd_path, args, envp);
	perror("minishell: execve error");
	exit(EXIT_FAILURE);
}
