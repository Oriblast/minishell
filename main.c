/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:06:01 by mounali           #+#    #+#             */
/*   Updated: 2023/10/02 21:06:12 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*pid_t	g_child_pid = -1;

char	*get_command_input(int *x)
{
	char	*cmd;

	terminal_setup();
	cmd = readline("$> ");
	if (!cmd)
	{
		ft_putstr_fd("\n", 1);
		exit(0);
	}
	add_history(cmd);
	if (is_empty_string(cmd))
	{
		free(cmd);
		*x = 1;
		return (NULL);
	}
	*x = 0;
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	int		x;

	(void)argc;
	(void)argv;
	x = 1;
	setup_signals();
	rl_bind_keyseq("\\C-\\", rl_insert);
	while (1)
	{
		if (x)
		{
			cmd = get_command_input(&x);
			if (!cmd)
				continue ;
		}
		env = execute_command(cmd, env);
		free(cmd);
		x = 1;
	}
	return (0);
}*/

#include "minishell.h"

pid_t	g_child_pid = -1;

char	*get_command_input(int *x)
{
	char	*cmd;

	terminal_setup();
	cmd = readline("$> ");
	if (!cmd)
	{
		ft_putstr_fd("\n", 1);
		exit(0);
	}
	add_history(cmd);
	if (is_empty_string(cmd))
	{
		free(cmd);
		*x = 1;
		return (NULL);
	}
	*x = 0;
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	int		x;
	t_vari	a;

	(void)argc;
	(void)argv;
	x = 1;
	setup_signals();
	rl_bind_keyseq("\\C-\\", rl_insert);
	while (1)
	{
		if (x)
		{
			cmd = get_command_input(&x);
			if (!cmd)
				continue ;
		}
		quote2(cmd, &a);
		verified(&a, cmd);
		if (a.k == -1)
			env = execute_command(cmd, env, &a);
		else
			printf("quote non fermer\n");
		free(a.car);
		free(a.cmd2);
		free(cmd);
		x = 1;
	}
	return (0);
}
