/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:11:04 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 21:00:05 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_command(t_command *cmd, char **envp)
{
	char	*full_cmd_path;
	char	**args;

	full_cmd_path = get_command_path(cmd, envp);
	if (!full_cmd_path)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	args = prepare_args(cmd, envp);
	if (execve(full_cmd_path, args, envp) == -1)
	{
		perror("minishell");
		free(full_cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	execute_extern_cmd(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execute_child_command(cmd, envp);
	else if (pid < 0)
	{
		perror("minishell: fork error");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		all_retour(&cmd->retour, &status);
	}
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static char	**initialize_args(t_command *cmd, char **envp, int count)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!args)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}
	args[0] = find_cmd_in_path(cmd->cmd_name, envp);
	if (!args[0])
	{
		perror("minishell: command not found");
		exit(EXIT_FAILURE);
	}
	return (args);
}

char	**construct_args_for_execve(t_command *cmd,
		char **envp, int include_full_path_as_arg)
{
	int		i;
	char	**args;
	int		index;
	int		j;

	i = count_args(cmd->args);
	args = initialize_args(cmd, envp, i);
	index = 0;
	j = 0;
	if (include_full_path_as_arg)
		j = 1;
	while (index < i)
	{
		args[index + j] = cmd->args[index];
		index++;
	}
	args[i + j] = NULL;
	return (args);
}
