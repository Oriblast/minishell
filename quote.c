/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:15:44 by ksongbe           #+#    #+#             */
/*   Updated: 2023/09/23 21:15:48 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	**quote(char *cmd)
{
	int	i;
	int	j;
	int k;
	int **jj;

	jj = (int **)malloc(3 * sizeof(int*));
	i = 0;
	while (i < 3)
	{
		jj[i] = (int *)malloc(100 * sizeof(int));
		i++;
	}
	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			jj[1][j] = i;
			j++;
		}
		if (cmd[i] == '"')
		{
			jj[0][k] = i;
			k++;
		}
		i++;
	}
	if (j % 2 == 0 || k % 2 == 0)
	{
		if (jj[1][0] < jj[0][0] && jj[1][j - 1] > jj[0][k - 1])
		{
			jj[2][0] = 2;
			jj[2][1] = jj[1][0];
			jj[2][2] = jj[1][j - 1];
			return (jj);
		}
		else if (jj[1][0] > jj[0][0] && jj[1][j - 1] < jj[0][k - 1])
		{
			jj[2][0] = 2;
			jj[2][1] = jj[0][0];
			jj[2][2] = jj[0][k - 1];
			return (jj);
		}
		else if (jj[1][0] > jj[0][k - 1] || jj[0][0] > jj[1][j - 1])
		{
			jj[2][0] = 4;
			jj[2][1] = jj[1][0];
			jj[2][2] = jj[1][j - 1];
			jj[2][3] = jj[0][0];
			jj[2][4] = jj[0][k - 1];
			return (jj);
		}
	}
	if (j % 2 == 1 || k % 2 == 1)
	{
		if (jj[1][j - 1] > jj[0][0] && jj[1][j - 1] < jj[0][k - 1])
		{
			jj[2][0] = 2;
			jj[2][1] = jj[0][0];
			jj[2][1] = jj[0][k - 1];
			return (jj);
		}
		else if (jj[0][k - 1] > jj[1][0] && jj[0][k - 1] < jj[1][j - 1])
		{
			jj[2][0] = 2;
			jj[2][1] = jj[1][0];
			jj[2][1] = jj[1][j - 1];
			return (jj);
		}
	}
	return (NULL);
}*/
void process_command(char *cmd) 
{
    pid_t pid = fork();

    if (pid == -1) {
        // Gestion d'erreur
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Code du processus fils
        execlp("sh", "sh", "-c", cmd, NULL);
        // Si execlp réussit, le code ci-dessous ne sera pas exécuté
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Code du processus parent
        int status;
        waitpid(pid, &status, 0);
        // Vous pouvez effectuer des opérations supplémentaires après l'exécution de la commande ici
    }
}