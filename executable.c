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
    write(1, "\n$> ", 4);
}

void    setup_signals(void) // gere les signaux
{
    struct sigaction sa;

    sa.sa_handler = sigchild;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; // RESTART = si des appels sys sont interrompus par ce signal ils sont redemedarres
                                             // NOCLDSTOP = empeche le signl SIGCHLD si les enfants s arretent pas s ils terminent         
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    signal(SIGINT, sigint); // signint pour gerer ctrl c
}

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
        waitpid(pid, &status, WUNTRACED);

}