/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:05:43 by mounali           #+#    #+#             */
/*   Updated: 2023/10/25 18:37:22 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **space_splits)
{
	int		j;

	j = 0;
	while (space_splits && space_splits[j])
		j++;
	return (j);
}

char	**extract_args(const char *input)
{
	char	**space_splits;
	char	**args;
	int		arg_count;
	int		j;

	space_splits = ft_split(input, ' ');
	arg_count = count_args(space_splits) - 1;
	args = malloc((arg_count + 2) * sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = strdup(space_splits[0]);
	j = 1;
	while (j <= arg_count)
	{
		args[j] = strdup(space_splits[j]);
		j++;
	}
	args[arg_count + 1] = NULL;
	free_str_array(space_splits);
	return (args);
}

// fn1_count_subcommands.c

void	fn2b_handle_memory_errors(t_subcommand *subcmd, t_command *command)
{
	if (!subcmd->args)
	{
		perror("Memory allocation error for command arguments");
		exit(EXIT_FAILURE);
	}
	if (!command)
	{
		perror("Error converting subcommand to command");
		exit(EXIT_FAILURE);
	}
}

void	fn2_fill_commands(t_command **commands,
		char **pipe_splits, int num_subcmds)
{
	t_subcommand	subcmd;
	int				i;
	char			*trimmed_command;

	i = 0;
	while (i < num_subcmds)
	{
		trimmed_command = trim(pipe_splits[i]);
		subcmd = fn2a_init_subcmd(trimmed_command);
		commands[i] = convert_subcommand_to_command(&subcmd);
		fn2b_handle_memory_errors(&subcmd, commands[i]);
		i++;
	}
}

t_command	**parse_subcommands_with_redirections(const char *cmd_input)
{
	char		**pipe_splits;
	t_command	**commands;
	int			num_subcmds;

	pipe_splits = ft_split(cmd_input, '|');
	num_subcmds = fn1_count_subcommands(pipe_splits);
	commands = fn1_init_commands_array(num_subcmds);
	fn2_fill_commands(commands, pipe_splits, num_subcmds);
	commands[num_subcmds] = NULL;
	free_str_array(pipe_splits);
	return (commands);
}
