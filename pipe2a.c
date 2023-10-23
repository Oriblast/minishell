/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 00:20:46 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 00:20:59 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fn1_count_subcommands(char **pipe_splits)
{
	int	i;

	i = 0;
	while (pipe_splits && pipe_splits[i])
		i++;
	return (i);
}

// fn2_handle_input_redirection.c
void	fn2_handle_input_redirection(t_subcommand *subcmd,
		char *trimmed_command)
{
	char	*redirection_part;

	if (strstr(trimmed_command, "<"))
	{
		redirection_part = strstr(trimmed_command, "<");
		*redirection_part = '\0';
		redirection_part = trim(redirection_part + 1);
		subcmd->input_redirect = strdup(redirection_part);
		if (!subcmd->input_redirect)
		{
			perror("Memory allocation error for input redirection");
			exit(EXIT_FAILURE);
		}
	}
}

// fn3_handle_output_redirection.c
void	fn3_handle_output_redirection(t_subcommand *subcmd,
		char *trimmed_command)
{
	char	*redirection_part;

	if (strstr(trimmed_command, ">"))
	{
		redirection_part = strstr(trimmed_command, ">");
		*redirection_part = '\0';
		redirection_part = trim(redirection_part + 1);
		subcmd->output_redirect = strdup(redirection_part);
		if (!subcmd->output_redirect)
		{
			perror("Memory allocation error for output redirection");
			exit(EXIT_FAILURE);
		}
	}
}

t_command	**fn1_init_commands_array(int num_subcmds)
{
	t_command	**commands;

	commands = malloc((num_subcmds + 1) * sizeof(t_command *));
	if (!commands)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	return (commands);
}

t_subcommand	fn2a_init_subcmd(char *trimmed_command)
{
	t_subcommand	subcmd;

	memset(&subcmd, 0, sizeof(t_subcommand));
	fn2_handle_input_redirection(&subcmd, trimmed_command);
	fn3_handle_output_redirection(&subcmd, trimmed_command);
	subcmd.args = extract_args(trim(trimmed_command));
	subcmd.cmd_name = subcmd.args[0];
	return (subcmd);
}
