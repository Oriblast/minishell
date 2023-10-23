/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:44:23 by mounali           #+#    #+#             */
/*   Updated: 2023/10/05 21:05:52 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

t_command	*convert_subcommand_to_command(t_subcommand *subcmd)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	cmd->cmd_name = strdup(subcmd->cmd_name);
	cmd->args = subcmd->args;
	if (subcmd->input_redirect)
		cmd->input_redirect = strdup(subcmd->input_redirect);
	else
		cmd->input_redirect = NULL;
	if (subcmd->output_redirect)
		cmd->output_redirect = strdup(subcmd->output_redirect);
	else
		cmd->output_redirect = NULL;
	cmd->output_type = 0;
	cmd->heredoc_delimiter = NULL;
	return (cmd);
}

void	free_command(t_command *cmd)
{
	char	**args_ptr;

	if (!cmd)
		return ;
	free(cmd->cmd_name);
	if (cmd->args)
	{
		args_ptr = cmd->args;
		while (*args_ptr)
		{
			free(*args_ptr);
			args_ptr++;
		}
		free(cmd->args);
	}
	free(cmd->input_redirect);
	free(cmd->output_redirect);
	free(cmd->heredoc_delimiter);
	free(cmd);
}

void	free_commands(t_command **commands)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (commands[i])
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
}
