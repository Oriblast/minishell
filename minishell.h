/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:00:55 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 17:00:57 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <ctype.h>

void echo_cmd(char *line, char **envp);
void    ft_putchar_fd(char c, int fd);
void    env_cmd(char **envp);
void    unset_cmd(char **envp, char *varname);
void    export_cmd(char *command, char ***envp);

#endif 