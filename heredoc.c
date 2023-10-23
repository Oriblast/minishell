/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:27:59 by mounali           #+#    #+#             */
/*   Updated: 2023/10/22 22:31:08 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_command *cmd)
{
	char	*line;
	char	tmp_filename[32];
	int		fd;

	strcpy(tmp_filename, "/tmp/minishell_heredoc_XXXXXX");
	fd = mkstemp(tmp_filename);
	if (fd == -1)
	{
		perror("minishell: error creating heredoc temporary file");
		exit(EXIT_FAILURE);
	}
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !strcmp(line, cmd->heredoc_delimiter))
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	cmd->input_redirect = strdup(tmp_filename);
}

void	clean_heredoc(t_command *cmd)
{
	remove(cmd->input_redirect);
	free(cmd->input_redirect);
	cmd->input_redirect = NULL;
}
