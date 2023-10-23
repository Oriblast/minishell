/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:47:25 by mounali           #+#    #+#             */
/*   Updated: 2023/10/23 22:47:34 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirection(t_command *cmd)
{
	int	fd;

	fd = open(cmd->input_redirect, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: input redirection error");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->output_type == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_redirect, flags, 0644);
	if (fd == -1)
	{
		perror("minishell: output redirection error");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_command *cmd)
{
	if (cmd->input_redirect)
		handle_input_redirection(cmd);
	if (cmd->output_redirect)
		handle_output_redirection(cmd);
}
