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
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>


void    echo_cmd(char *line, char **envp);
void    ft_putchar_fd(char c, int fd);
void    env_cmd(char **envp);
void    unset_cmd(char **envp, char *varname);
void    export_cmd(char *command, char ***envp);
void    execute_extern_cmd(char *cmd, char **args, char **envp);
void    setup_signals(void);
void    execute_cmd_with_path(char *cmd, char **args, char **envp);
char *find_cmd_in_path(char *cmd, char **envp);
void    execute_with_pipes(char *cmd, char **env);

//*******UTILS*********
char    *ft_strjoin(char *path, char *cmd);
char	**ft_split(const char *str, char c);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);
void	free_str_array(char **strs);
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strstr(const char *haystack, const char *needle);
int	count_str_array(char **array);
char    *ft_strncpy(char *dst, const char *src, size_t len);
int	is_empty_string(char *str);
char **my_completion(const char *text, int start, int end);

#endif 