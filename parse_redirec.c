/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:40:55 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 01:17:27 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("Error allocating memory for command structure");
		exit(EXIT_FAILURE);
	}
	cmd->cmd_name = NULL;
	cmd->args = NULL;
	cmd->input_redirect = NULL;
	cmd->output_redirect = NULL;
	cmd->output_type = NORMAL;
	cmd->heredoc_delimiter = NULL;
	return (cmd);
}

char	*extract_filename(char *start)
{
	char	*end;

	while (*start == ' ')
		start++;
	end = start;
	while (*end && *end != ' ' && *end != '<' && *end != '>')
		end++;
	return (strndup(start, end - start));
}

t_command	*init_command_redirection(char *input, t_command *cmd)
{
	char	*position_redirection;

	position_redirection = strchr(input, '<');
	if (position_redirection)
	{
		*position_redirection = '\0';
		cmd->input_redirect = extract_filename(position_redirection + 1);
	}
	position_redirection = strstr(input, ">>");
	if (position_redirection)
	{
		*position_redirection = '\0';
		cmd->output_redirect = extract_filename(position_redirection + 2);
		cmd->output_type = APPEND;
	}
	else
	{
		position_redirection = strchr(input, '>');
		if (position_redirection)
		{
			*position_redirection = '\0';
			cmd->output_redirect = extract_filename(position_redirection + 1);
		}
	}
	return (cmd);
}

t_command	*traiter_heredoc(char *input, t_command *cmd)
{
	char	*position_heredoc;

	position_heredoc = strstr(input, "<<");
	if (position_heredoc)
	{
		*position_heredoc = '\0';
		cmd->heredoc_delimiter = extract_filename(position_heredoc + 2);
	}
	return (cmd);
}

t_command	*traiter_arguments(char *input, t_command *cmd)
{
	char	*token;
	char	*tmp;
	char	*rest;
	int		compteur;

	compteur = 0;
	tmp = strdup(input);
	rest = tmp;
	token = strtok_r(rest, " ", &rest);
	while (token)
	{
		if (compteur == 0)
			cmd->cmd_name = strdup(token);
		else
		{
			cmd->args = realloc(cmd->args, sizeof(char *) * (compteur + 2));
			cmd->args[compteur - 1] = strdup(token);
		}
		compteur++;
		token = strtok_r(rest, " ", &rest);
	}
	if (cmd->args)
		cmd->args[compteur - 1] = NULL;
	free(tmp);
	return (cmd);
}
