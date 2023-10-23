/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:57:53 by mounali           #+#    #+#             */
/*   Updated: 2023/10/23 20:58:04 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_command **commands)
{
	int	num_cmds;

	num_cmds = 0;
	while (commands[num_cmds])
		num_cmds++;
	return (num_cmds);
}

void	create_pipes(int num_cmds, int pipe_fds[][2])
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("minishell: pipe error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int num_cmds, int pipe_fds[][2])
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		close(pipe_fds[j][0]);
		close(pipe_fds[j][1]);
		j++;
	}
}

void	close_pipes_and_wait(int num_cmds, int pipe_fds[10][2])
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
}
