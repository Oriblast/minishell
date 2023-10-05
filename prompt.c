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

void	handle_external_command(char *cmd, char **env)
{
	char	**split_cmd;
	char	*full_cmd_path;

	split_cmd = ft_split(cmd, ' ');
	full_cmd_path = find_cmd_in_path(split_cmd[0], env);
	if (full_cmd_path)
	{
		execute_extern_cmd(full_cmd_path, split_cmd, env, 1);
		free(full_cmd_path);
	}
	else
		ft_putstr_fd("minishell: command not found\n", 2);
	free_str_array(split_cmd);
}

char	**execute_command(char *cmd, char **env)
{
	char	**pipe_cmds;

	if (check(cmd, "cd", 0) == 1)
		cdd(cmd);
	else if (check(cmd, "pwd", 0) == 1)
		cwd();
	else if (check(cmd, "echo", 0) == 1)
		echo_cmd(cmd, env);
	else if (check(cmd, "env", 0) == 1)
		env_cmd(env);
	else if (check(cmd, "unset", 1) == 1)
		unset_cmd(env, cmd + 6);
	else if (strcmp(cmd, "exit") == 0)
		exit_cmd();
	else if (check(cmd, "export", 0) == 1)
		env = export_cmd(cmd + 7, &env);
	else if (ft_strstr(cmd, "|") != NULL)
	{
		pipe_cmds = ft_split(cmd, '|');
		execute_pipe_command(pipe_cmds, env);
		free_str_array(pipe_cmds);
	}
	else
		handle_external_command(cmd, env);
	return (env);
}
