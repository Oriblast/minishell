/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:05:43 by mounali           #+#    #+#             */
/*   Updated: 2023/10/05 21:24:10 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_read_write_fd(t_pipe_info *info)
{
	if (info->i == 0)
		info->cur_read_fd = NULL;
	else
		info->cur_read_fd = &info->pipes[info->i - 1][0];
	if (info->i == info->num_cmds - 1)
		info->cur_write_fd = NULL;
	else
		info->cur_write_fd = &info->pipes[info->i][1];
}

void	handle_pipe_execution(t_pipe_info *info)
{
	set_read_write_fd(info);
	execute_single_command_in_pipe(
		info->cmds[info->i],
		info->cur_read_fd,
		info->cur_write_fd,
		info->env);
	if (info->cur_write_fd)
		close(*(info->cur_write_fd));
}

void	execute_pipe_command(char **cmds, char **env)
{
	t_pipe_info	info;

	info.num_cmds = 0;
	while (cmds[info.num_cmds])
		info.num_cmds++;
	initialize_pipes(info.num_cmds, &(info.pipes));
	info.i = -1;
	info.cmds = cmds;
	info.env = env;
	while (++info.i < info.num_cmds)
		handle_pipe_execution(&info);
	close_pipe_fds(info.num_cmds, info.pipes);
	free_pipe_memory(info.num_cmds, info.pipes);
}
