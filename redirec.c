/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:20:39 by mounali           #+#    #+#             */
/*   Updated: 2023/09/29 22:20:50 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_with_redirections(t_command *cmd, char **env) {
    if (cmd->heredoc_delimiter) {
        handle_heredoc(cmd);
    }

    int saved_stdout = -1;
    int saved_stdin = -1;

    if (cmd->output_redirect) {
        int flags = O_WRONLY | O_CREAT;

        if (cmd->output_type == APPEND) {
            flags |= O_APPEND;
        } else {
            flags |= O_TRUNC;
        }

        int fd_out = open(cmd->output_redirect, flags, 0644);
        if (fd_out == -1) {
            perror("minishell: output redirection error");
            return;
        }
        saved_stdout = dup(STDOUT_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    if (cmd->input_redirect) {
        int fd_in = open(cmd->input_redirect, O_RDONLY);
        if (fd_in == -1) {
            perror("minishell: input redirection error");
            return;
        }
        saved_stdin = dup(STDIN_FILENO);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    handle_external_command(cmd, env);

    if (saved_stdout != -1) {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }

    if (saved_stdin != -1) {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }

    if (cmd->heredoc_delimiter) {
        remove(cmd->input_redirect);
        free(cmd->input_redirect);
        cmd->input_redirect = NULL;
    }
}

char *create_heredoc_file(const char *delimiter) {
    char buffer[1024];
    char tmp_filename[] = "/tmp/minishell_heredoc_XXXXXX";
    int tmp_fd = mkstemp(tmp_filename);
    
    if (tmp_fd == -1) {
        perror("minishell: heredoc error");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        
        if (strncmp(buffer, delimiter, strlen(delimiter)) == 0) {
            break;
        }
        
        write(tmp_fd, buffer, strlen(buffer));
    }

    close(tmp_fd);
    return strdup(tmp_filename);
}

void handle_heredoc(t_command *cmd) {
    char *line = NULL;
    char tmp_filename[] = "/tmp/minishell_heredoc_XXXXXX";
    int fd = mkstemp(tmp_filename);

    if (fd == -1) {
        perror("minishell: error creating heredoc temporary file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        line = readline("> ");
        if (!line) break;
        if (strcmp(line, cmd->heredoc_delimiter) == 0) break;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);

    cmd->input_redirect = strdup(tmp_filename);
}
