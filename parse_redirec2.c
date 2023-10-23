/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:18:35 by mounali           #+#    #+#             */
/*   Updated: 2023/10/24 01:18:43 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_redirections(char *input)
{
	t_command	*cmd;

	cmd = init_command();
	cmd = traiter_heredoc(input, cmd);
	cmd = init_command_redirection(input, cmd);
	cmd = traiter_arguments(input, cmd);
	return (cmd);
}
