/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:24:28 by ksongbe           #+#    #+#             */
/*   Updated: 2023/10/17 22:15:54 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verified(t_vari *a, char *cmd)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	a->k = 0;
	while (i < ft_strlen(cmd))
	{
		if (a->car[i] == 1)
		{
			a->cmd2[j] = cmd[i];
			j++;
		}
		if (a->car[i] == 0)
			a->k++;
		i++;
	}
	a->cmd2[j] = '\0';
	if (a->k % 2 == 0)
		a->k = -1;
}

int	quote3(char	*cmd, int i, char c, t_vari *a)
{
	a->car[i] = 0;
	i++;
	while (cmd[i] && cmd[i] != c)
	{
		a->car[i] = 1;
		i++;
	}
	if (cmd[i] == c)
		a->car[i] = 0;
	return (i);
}

void	quote2(char	*cmd, t_vari *a)
{
	int	i;

	i = 0;
	a->car = malloc(sizeof(int) * ft_strlen(cmd));
	a->cmd2 = malloc(sizeof(int) * ft_strlen(cmd));
	while (cmd[i])
	{
		a->car[i] = 1;
		if (cmd[i] == '\'')
			i = quote3(cmd, i, '\'', a);
		else if (cmd[i] == '"')
			i = quote3(cmd, i, '"', a);
		i++;
	}
}
