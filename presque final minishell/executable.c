/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:33:56 by mounali           #+#    #+#             */
/*   Updated: 2023/10/01 20:10:26 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigchild(int i)
{
	(void)i;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void	sigint(int i)
{
	(void)i;
	if (g_child_pid > 0)
		kill(g_child_pid, SIGINT);
	write(1, "\n$> ", 4);
}

void	sigquit(int i)
{
	(void)i;
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigchild;
	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGCHLD);
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	sa.sa_handler = sigint;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	execute_helper(pid_t pid, char *cmd, char **args, char **envp)
{
	if (pid == 0)
	{
		if (execve(cmd, args, envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		g_child_pid = pid;
		waitpid(pid, NULL, WUNTRACED);
		g_child_pid = -1;
	}
}
