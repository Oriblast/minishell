/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:19:59 by mounali           #+#    #+#             */
/*   Updated: 2023/10/25 21:58:04 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_arg_processing(t_command *cmd, int *i, char **envp)
{
	if (cmd->args[*i][0] == '\'' || cmd->args[*i][0] == '"')
		print_between_quotes(cmd->args[*i], i, envp);
	else if (cmd->args[*i][0] == '$')
		handle_var_substitution(cmd->args[*i], i, envp);
	else
		ft_putstr_fd(cmd->args[*i], 1);
	if (cmd->args[*i + 1])
		ft_putchar_fd(' ', 1);
	(*i)++;
}

int	g_last_return_code = 0;

void	echo_cmd(t_command *cmd, char **envp)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (!cmd->args || !cmd->args[0])
		return (ft_putchar_fd('\n', 1));
	if (strcmp(cmd->args[0], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		if (strcmp(cmd->args[i], "$?") == 0)
			ft_putstr_fd(ft_itoa(g_last_return_code), 1);
		else
			handle_arg_processing(cmd, &i, envp);
		if (cmd->args[++i] && newline != 0)
			ft_putchar_fd(' ', 1);
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
