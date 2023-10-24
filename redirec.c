/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:20:39 by mounali           #+#    #+#             */
/*   Updated: 2023/10/25 00:29:20 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static void	handle_output_redirect(t_command *cmd, int *saved_stdout)
{
	int		fd_out;
	int		flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->output_type == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(cmd->output_redirect, flags, 0644);
	if (fd_out == -1)
	{
		perror("minishell: output redirection error");
		return ;
	}
	*saved_stdout = dup(STDOUT_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

static void	handle_input_redirect(t_command *cmd, int *saved_stdin)
{
	int		fd_in;

	fd_in = open(cmd->input_redirect, O_RDONLY);
	if (fd_in == -1)
	{
		perror("minishell: input redirection error");
		return ;
	}
	*saved_stdin = dup(STDIN_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

static void	restore_fds(int saved_stdout, int saved_stdin)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

void	execute_with_redirections(t_command *cmd, char **env)
{
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = -1;
	saved_stdin = -1;
	if (cmd->heredoc_delimiter)
		handle_heredoc(cmd);
	if (cmd->output_redirect)
		handle_output_redirect(cmd, &saved_stdout);
	if (cmd->input_redirect)
		handle_input_redirect(cmd, &saved_stdin);
	handle_external_command(cmd, env);
	restore_fds(saved_stdout, saved_stdin);
	if (cmd->heredoc_delimiter)
		clean_heredoc(cmd);
}
