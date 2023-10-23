/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:11:04 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 01:49:24 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **prepare_args(t_command *cmd, char **envp)
{
    return construct_args_for_execve(cmd, envp, 1);
}

static char *get_command_path(t_command *cmd, char **envp)
{
    if (strncmp(cmd->cmd_name, "/", 1) == 0)
    {
        return strdup(cmd->cmd_name);
    }
    else
    {
        return find_cmd_in_path(cmd->cmd_name, envp);
    }
}

static void execute_child_command(t_command *cmd, char **envp)
{
    char *full_cmd_path = get_command_path(cmd, envp);
    
    if (!full_cmd_path) {
        perror("minishell");
        exit(EXIT_FAILURE);
    }

    char **args = prepare_args(cmd, envp);
    if (execve(full_cmd_path, args, envp) == -1) {
        perror("minishell");
        free(full_cmd_path);
        exit(EXIT_FAILURE);
    }
}

void execute_extern_cmd(t_command *cmd, char **envp)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        execute_child_command(cmd, envp);
    } else if (pid < 0) {
        perror("minishell: fork error");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &status, 0);
        all_retour(&cmd->retour, &status);
    }
}


/*char **construct_args_for_execve(t_command *cmd, char **envp, int include_full_path_as_arg) {
    int i = 0;

    while (cmd->args && cmd->args[i]) {
        i++;
    }

    char **args = (char **)malloc(sizeof(char *) * (i + 2));
    if (!args) {
        perror("minishell: memory allocation error");
        exit(EXIT_FAILURE);
    }

    char *full_cmd_path = find_cmd_in_path(cmd->cmd_name, envp);
    if (!full_cmd_path) {
        perror("minishell: command not found");
        exit(EXIT_FAILURE);
    }

    args[0] = full_cmd_path;
    int start_index = include_full_path_as_arg ? 1 : 0;
    for (int j = 0; j < i; j++) {
        args[j + start_index] = cmd->args[j];
    }
    args[i + start_index] = NULL;

    for (int k = 0; args && args[k]; k++) {
        //printf("%s ", args[k]);
    }
    //printf("\n");

    return args;
}
*/

static int count_args(char **args)
{
    int i = 0;
    while (args && args[i]) {
        i++;
    }
    return i;
}

static char **initialize_args(t_command *cmd, char **envp, int count)
{
    char **args = (char **)malloc(sizeof(char *) * (count + 2));
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
    return args;
}

char	**construct_args_for_execve(t_command *cmd,
		char **envp, int include_full_path_as_arg)
{
	int	i = count_args(cmd->args);
	char	**args = initialize_args(cmd, envp, i);
	int	index = 0;
	int	j = 0;

	if (include_full_path_as_arg)
	{
		j = 1;
	}
	while (index < i)
	{
		args[index + j] = cmd->args[index];
		index++;
	}
	args[i + j] = NULL;
	return (args);
}
