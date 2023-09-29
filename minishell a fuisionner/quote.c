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

int	quote(char *cmd, char **env) 
{
    pid_t	pid;
	char	**args;
	int		status;

	pid = fork();
    if (pid == -1) 
	{
        perror("fork");
        return (0);
    }
	else if (pid == 0)
	{
        // Code du processus fils

        // Parse la commande en utilisant des espaces comme délimiteurs
        args = ft_split(cmd, ' ');

        if (args == NULL) {
            perror("ft_split");
            exit(EXIT_FAILURE);
        }

        // Exécute la commande avec execve
        execve(args[0], args, env);
        // En cas d'échec de execve
        perror("execve");
		free_str_array(args);
        exit(EXIT_FAILURE);
    } 
	else
        waitpid(pid, &status, 0);
	return (1);
}