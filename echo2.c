/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:19:59 by mounali           #+#    #+#             */
/*   Updated: 2023/10/01 20:20:09 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_command *cmd, char **envp)
{
	int		i;
	//int		new_line;

	i = 0;

    if (!cmd->args || !cmd->args[0]) {
        ft_putchar_fd('\n', 1);
        return;
    }

	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '\'' || cmd->args[i][0] == '"')
			print_between_quotes(cmd->args[i], &i, envp); 
		else if (cmd->args[i][0] == '$')
			handle_var_substitution(cmd->args[i], &i, envp);
		else
			ft_putstr_fd(cmd->args[i], 1);

        // Si ce n'est pas le dernier argument, ajoutez un espace entre eux
        if (cmd->args[i + 1]) {
            ft_putchar_fd(' ', 1);
        }
		i++;
	}

	ft_putchar_fd('\n', 1);
}
