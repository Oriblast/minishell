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

void	echo_cmd(char *line, char **envp)
{
	int		i;
	int		new_line;

	i = 0;
	while (line[i] && line[i] != 'e')
		i++;
	i += 5;
	while (line[i] && isspace(line[i]))
		i++;
	new_line = parse_echo_flags(line, &i);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			print_between_quotes(line, &i, envp);
		else if (line[i] == '$')
			handle_var_substitution(line, &i, envp);
		else
			ft_putchar_fd(line[i++], 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	else
		write(1, "%%", 2);
}
