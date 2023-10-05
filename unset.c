/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:17:44 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 21:58:15 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **envp, char *varname)
{
	int	i;
	int	j;
	int	varlen;

	i = 0;
	varlen = strlen(varname);
	while (envp[i])
	{
		if (strncmp(envp[i], varname, varlen) == 0 && envp[i][varlen] == '=')
		{
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}
