/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:24:28 by ksongbe           #+#    #+#             */
/*   Updated: 2023/10/16 00:26:48 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	verified(t_vari *a, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (a->car[i])
	{
		if (a->car[i] == 1)
		{
			a->cmd2[j] = cmd[i];
			j++;
		}
		i++;
	}
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
	if (a->cmd[i] == c)
		a->car[i] = 0;
	return (i);
}

void	quote2(char	*cmd, t_vari *a)
{
	int	*car;
	int	i;

	i = 0;
	a->car = malloc(sizeof(int) * ft_strlen(cmd));
	a->cmd2 = malloc(sizeof(int) * ft_strlen(cmd))
	while (cmd[i])
	{
		a->car[i] = 1;
		if (cmd[i] == '\'')
			i = quote3(cmd, i, '\'', a->car);
		else if (cmd[i] == '"')
			i = quote3(cmd, i, '"', a->car);
		i++;
	}
}
