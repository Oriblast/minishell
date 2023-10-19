/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:30 by ksongbe           #+#    #+#             */
/*   Updated: 2023/09/21 21:59:27 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_setup(void)
{
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void	exit_cmd(void)
{
	ft_putstr_fd("Merci d'avoir utilisé notre mini-shell ! Au revoir !\n", 1);
	rl_clear_history();
	exit(0);
}

void handle_external_command(t_command *cmd, char **env) 
{
    char *full_cmd_path;

    full_cmd_path = find_cmd_in_path(cmd->cmd_name, env);
    if (full_cmd_path) {
        execute_extern_cmd(cmd, env);
        free(full_cmd_path);
    } else {
        ft_putstr_fd("minishell: command not found\n", 2);
    }
}

char **execute_command(char *cmd_input, char **env) {
    t_command *cmd = parse_redirections(cmd_input);

    if (cmd->input_redirect || cmd->output_redirect) {
        execute_with_redirections(cmd, env);
        free_command(cmd);
        return env;
    }

    if (strcmp(cmd->cmd_name, "cd") == 0) {
        cdd(cmd->args[0]);
    }
    else if (strcmp(cmd->cmd_name, "pwd") == 0) {
        cwd();
    }
    else if (strcmp(cmd->cmd_name, "echo") == 0) {
        echo_cmd(cmd, env);
    }
    else if (strcmp(cmd->cmd_name, "env") == 0) {
        env_cmd(env);
    }
    else if (strcmp(cmd->cmd_name, "unset") == 0) {
        unset_cmd(env, cmd->args[0]);  
    }
    else if (strcmp(cmd->cmd_name, "exit") == 0) {
        exit_cmd();
    }
    else if (strcmp(cmd->cmd_name, "export") == 0) {
        env = export_cmd(cmd->args[0], &env);
    }
    else if (ft_strstr(cmd->cmd_name, "|") != NULL) {
        char **pipe_cmds = ft_split(cmd_input, '|');
        execute_pipe_command(pipe_cmds, env);
        free_str_array(pipe_cmds);
    }
    else {
        handle_external_command(cmd, env);
    }

    free_command(cmd);
    return env;
}
