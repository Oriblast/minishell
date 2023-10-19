/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:11:04 by mounali           #+#    #+#             */
/*   Updated: 2023/10/01 20:11:16 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_extern_cmd(t_command *cmd, char **envp) {
    pid_t pid = fork();

    if (pid == 0) {
        // Enfant : Exécuter la commande externe
        char **args = construct_args_for_execve(cmd);
        
        char *full_cmd_path;
        if (strncmp(cmd->cmd_name, "/", 1) == 0) { // Vérifie si commande démarre avec '/'
            full_cmd_path = strdup(cmd->cmd_name);
        } else {
            full_cmd_path = find_cmd_in_path(cmd->cmd_name, envp);
        }

        if (!full_cmd_path) {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
        
        if (execve(full_cmd_path, args, envp) == -1) {
            perror("minishell");
            free(full_cmd_path);
            exit(EXIT_FAILURE);
        }
        // Pas de free ici car execve remplace le processus

    } else if (pid < 0) {
        // Erreur lors du fork
        perror("minishell: fork error");
        exit(EXIT_FAILURE);
    } else {
        // Parent : Attendre le processus enfant
        wait(NULL);
    }
}


char **construct_args_for_execve(t_command *cmd) {
    // Construit les arguments pour 'execve'
    int i = 0;
    while (cmd->args && cmd->args[i]) {
        i++;
    }
    char **args = (char **)malloc(sizeof(char *) * (i + 2));
    args[0] = cmd->cmd_name;
    for (int j = 0; j < i; j++) {
        args[j + 1] = cmd->args[j];
    }
    args[i + 1] = NULL;
    return args;
}

