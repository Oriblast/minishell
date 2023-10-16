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

#include "minishell.h"

void	verified(t_vari *a, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	a->k = 0;
	while (i < ft_strlen(cmd))
	{
		if (a->car[i] == 1)
		{
			a->cmd2[j] = cmd[i];
			printf("%c", a->cmd2[j]);
			j++;
		}
		if (a->car[i] == 0)
			a->k++;
		i++;
	}
//	printf("\nok%dok\n\n", i);
	a->cmd2[j] = 0;
	if (a->k % 2 == 0)
		a->k = 1;
	else
		a->k = 0;
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
	int	*car;
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

int	main()
{
	t_vari	a;
	char	s[] = "\"\"\"'''\"\"\"ooo\"\"\"'''\"\"\"\""; 
	char	*s1;

	s1 = s;
	//printf("%s\n", s);
	quote2(s1, &a);
	verified(&a, s1);
	int i = 0;
	/*while (i < ft_strlen(s1))
	{
		printf("%d\n", a.car[i]);
		i++;
	}*/
	printf("\nok%sok\n", a.cmd2);
}