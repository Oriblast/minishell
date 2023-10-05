/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:10:24 by mounali           #+#    #+#             */
/*   Updated: 2023/10/05 21:10:35 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(int num_cmds, int **pipes)
{
	int	i;

	i = -1;
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			close(pipes[i][1]);
		if (i > 0)
			close(pipes[i - 1][0]);
	}
}

void	free_pipe_memory(int num_cmds, int **pipes)
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
		free(pipes[i]);
	free(pipes);
}
