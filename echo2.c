/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:19:59 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 21:40:57 by mounali          ###   ########.fr       */
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

void	echo_cmd(t_command *cmd, char **envp)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	while (cmd->args[i])
		handle_arg_processing(cmd, &i, envp);
	ft_putchar_fd('\n', 1);
}
