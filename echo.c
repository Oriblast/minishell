/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:08:41 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 17:08:44 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

char    *get_env_value(char *key, char **envp)
{
    int i;
    int key_len;
    char    *env_entry;

    i = 0;
    key_len = strlen(key);
    while (envp[i])
    {
        if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
            return (&envp[i][key_len + 1]);
        i++;
    }
    return (NULL);
}

void handle_var_substitution(char *line, int *i, char **envp)
{
    int var_len;
    int end;
    char var_key[255];
    char *value;

    int start = (*i) + 1; 
    
    end = start;
    while (line[end] && (isalnum(line[end]) || line[end] == '_'))
        end++;

    var_len = end - start;
    strncpy(var_key, &line[start], var_len);
    var_key[var_len] = '\0';

    value = get_env_value(var_key, envp);
    if (value)
    {
        int j = 0;
        while (value[j])
        {
            ft_putchar_fd(value[j], 1);
            j++;
        }   
    }

    *i = end; 
}



void print_between_quotes(char *line, char quote, int *i, char **envp)
{
    (*i)++;
    while (line[*i] && line[*i] != quote)
    {
        if (line[*i] == '$')
            handle_var_substitution(line, i, envp);
        else
        {
            ft_putchar_fd(line[*i], 1); 
            (*i)++;
        }
    }
}



void echo_cmd(char *line, char **envp)
{
    int i = 5;
    int new_line = 1;

    while (line[i] && isspace(line[i]))
        i++; 

    if (line[i] == '-' && line[i + 1] == 'n' && isspace(line[i + 2]))
    {
        new_line = 0;
        i += 2;
        while (line[i] && isspace(line[i]))
            i++; 
    }

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
            print_between_quotes(line, line[i], &i, envp);
        else if (line[i] == '$')
            handle_var_substitution(line, &i, envp);
        else
        {
            ft_putchar_fd(line[i], 1);
            i++;
        }
    }

    if (new_line)
        ft_putchar_fd('\n', 1);
    else
        printf("%%");
}