/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:34:37 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 17:34:39 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_cmd(char **envp)
{
    int i;
    i = 0;

    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}

char *get_path_from_envp(char **envp)
{
    int i = 0;
    char *prefix = "PATH=";
    while (envp[i])
    {
        if (ft_strncmp(envp[i], prefix, 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}


char *find_cmd_in_path(char *cmd, char **envp)
{
    struct stat st;

    if (cmd[0] == '/')
    {
        if (stat(cmd, &st) == 0 && st.st_mode & S_IXUSR)
        {
            return ft_strdup(cmd); // renvoie la commande comme elle est
        }
    }

    char    *path;
    char    **paths;
    char    *full_cmd;
    int     i;
    
    path = get_path_from_envp(envp);

    if (!path)
        return (NULL);
    paths = ft_split(path, ':');
    i = 0;
    while (paths[i])
    {
        full_cmd = ft_strjoin(paths[i], cmd);

         //printf("checking for command in: %s\n", full_cmd);

        if(stat(full_cmd, &st) == 0 && st.st_mode & S_IXUSR) // Verifie si la commande est executable
        {
            free_str_array(paths); // libere un tableau de chaine
            return (full_cmd);
        }
        free(full_cmd);
        i++;
    }
    free_str_array(paths);
    return (NULL);
}

void    execute_cmd_with_path(char *cmd, char **args, char **envp)
{
    char    *full_cmd;

    if ((full_cmd = find_cmd_in_path(cmd, envp)))
    {
        execve(full_cmd, args, envp);
        free(full_cmd);
    }
    else
    {
        ft_putstr_fd("minishell: command not foudn: ", 2);
        ft_putendl_fd(cmd, 2);
    }

}