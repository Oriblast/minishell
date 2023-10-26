/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:30 by ksongbe           #+#    #+#             */
/*   Updated: 2023/10/22 21:17:18 by mounali          ###   ########.fr       */
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

void	handle_external_command(t_command *cmd, char **env)
{
	char	*full_cmd_path;

	full_cmd_path = find_cmd_in_path(cmd->cmd_name, env);
	if (full_cmd_path)
	{
		execute_extern_cmd(cmd, env);
		free(full_cmd_path);
	}
	else
		ft_putstr_fd("minishell: command not found\n", 2);
}

void	process_command(t_command *cmd, char **env, t_vari *a)
{
	if (cmd->input_redirect || cmd->output_redirect || cmd->heredoc_delimiter)
		execute_with_redirections(cmd, env);
	else if (!strcmp(cmd->cmd_name, "cd"))
		cdd(cmd->args[0]);
	else if (!strcmp(cmd->cmd_name, "pwd"))
		cwd();
	else if (!strcmp(cmd->cmd_name, "echo"))
		echo_cmd(parse_redirections(a->cmd2), env);
	else if (!strcmp(cmd->cmd_name, "env"))
		env_cmd(env);
	else if (!strcmp(cmd->cmd_name, "unset"))
		unset_cmd(env, cmd->args[0]);
	else if (!strcmp(cmd->cmd_name, "exit"))
		exit_cmd();
	else if (!strcmp(cmd->cmd_name, "export"))
		env = export_cmd(cmd->args[0], &env);
	else
		handle_external_command(cmd, env);
}

char	**execute_command(char *cmd_input, char **env, t_vari *a)
{
	t_command	*cmd;
	t_command	**pipe_commands;

	if (ft_strstr(cmd_input, "|"))
	{
		pipe_commands = parse_subcommands_with_redirections(cmd_input);
		execute_pipelines(pipe_commands, env);
		free_commands(pipe_commands);
		return (env);
	}
	if (checkstar(cmd_input) == 1)
	{
		star(cmd_input, env);
		return (env);
	}
	
	cmd = parse_redirections(cmd_input);
	process_command(cmd, env, a);
	free_command(cmd);
	return (env);
}
