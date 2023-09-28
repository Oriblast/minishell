/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:33:56 by mounali           #+#    #+#             */
/*   Updated: 2023/09/23 20:33:58 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sigchild(int i) // nettoie le processus enfant pour ne pas faire de zombie
{
    (void)i;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void    sigint(int i) // juste pour gerer le ctrl c
{
    (void)i;
    if (g_child_pid > 0) 
        kill(g_child_pid, SIGINT);

    write(1, "\n$> ", 4);
}

void sigquit(int i) // ctrl '\'
{
    (void)i;
    //write(1, "\nReceived SIGQUIT\n", 18); 
}


void setup_signals(void)
{
    struct sigaction sa;

    // Pour SIGCHLD
    sa.sa_handler = sigchild;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGCHLD);

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    // Pour SIGINT
    sa.sa_handler = sigint;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    // Pour SIGQUIT
    // Ignorer SIGQUIT
    signal(SIGQUIT, SIG_IGN);

    /*sa.sa_handler = sigquit; // Utilisez le gestionnaire silencieux pour SIGQUIT
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGQUIT, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }*/
}


/*void    setup_signals(void) // gere les signaux
{
    struct sigaction sa;

    sa.sa_handler = sigchild;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; // RESTART = si des appels sys sont interrompus par ce signal ils sont redemedarres
                                             // NOCLDSTOP = empeche le signl SIGCHLD si les enfants s arretent pas s ils terminent 
    sigemptyset(&sa.sa_mask); //nettoyage des bits du masque de signal
    sigaddset(&sa.sa_mask, SIGCHLD); // ajout de SIGCHLD au masque
    sigaddset(&sa.sa_mask, SIGINT); // pareil pour le SIGINT

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    signal(SIGINT, sigint); // signint pour gerer ctrl c
    // Pour SIGINT
    sa.sa_handler = sigint; // réglez le gestionnaire pour SIGINT
    sigemptyset(&sa.sa_mask); // nettoie tous les bits du masque de signaux
    
    sa.sa_handler = sigquit;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGQUIT, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }
    // Ignorer SIGQUIT
    signal(SIGQUIT, SIG_IGN);


    if (sigaction(SIGINT, &sa, NULL) == -1) // Utilisez sigaction pour SIGINT au lieu de signal pour une meilleure portabilité
    {
        perror("sigaction");
        exit(1);
    }
}*/

void    execute_extern_cmd(char *cmd, char **args, char **envp)
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd, args, envp) == -1)
            perror("minishell");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("minishell");
    else 
    {
        g_child_pid = pid;
        waitpid(pid, &status, WUNTRACED);
        g_child_pid = -1;
    }
}