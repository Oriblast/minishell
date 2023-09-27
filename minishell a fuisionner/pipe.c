/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:44:23 by mounali           #+#    #+#             */
/*   Updated: 2023/09/26 22:44:27 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    configure_pipes(int i, int num_segments, int pipes [][2]) // sert juste a rediriger lentree/sortie standard
{
    int     j;

    j = 0;
    if (i != 0) // pas le premier segment donc doit lire de la sortie prec
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i != num_segments  - 1) // pas le dernier seg donc ecris sur l entree du seg suivant
        dup2(pipes[i][1], STDOUT_FILENO);
    while (j < num_segments - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }

}

void    execute_segment(char *segment, char **env)
{
    char    **split_segment;
    char    *full_cmd_path;

    split_segment = ft_split(segment, ' ');
    full_cmd_path = find_cmd_in_path(split_segment[0], env);
    execute_extern_cmd(full_cmd_path, split_segment, env);
    exit(0);   
}

void    execute_with_pipes(char *cmd, char **env)
{
    char **segments;
    int     num_segments;
    int     pipes[3000][2]; // limiter a 3000 commandes peux etre changer
    int     i;

    i = 0;
    segments = ft_split(cmd, '|');
    num_segments = count_str_array(segments);

    while (i < num_segments - 1) // pour chaque seg un pipe est cree
    {
        if (pipe(pipes[i]) == -1)
            exit(EXIT_FAILURE);
        i++;
    }
    i = 0;
    while (i < num_segments) // pour chaque seg un nouveau processus est cree avec fork
    {
        if (fork() == 0)
        {
            configure_pipes(i, num_segments, pipes);
            execute_segment(segments[i], env);
        }
        i++;
    }

    i = 0;
    while (i < num_segments - 1) // fermeture des descripteurs de pipe
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    i = 0;
    while (i < num_segments) // attente de la fin de tous les enfants a table
    {
        wait(NULL);
        i++;
    }

    free_str_array(segments);
}