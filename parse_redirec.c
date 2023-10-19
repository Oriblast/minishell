/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:40:55 by mounali           #+#    #+#             */
/*   Updated: 2023/09/29 22:41:03 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *init_command() {
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) {
        perror("Error allocating memory for command structure");
        exit(EXIT_FAILURE);
    }
    cmd->cmd_name = NULL;
    cmd->args = NULL;
    cmd->input_redirect = NULL;
    cmd->output_redirect = NULL;
    cmd->output_type = NORMAL;
    cmd->heredoc_delimiter = NULL;
    return cmd;
}

void free_command(t_command *cmd) {
    free(cmd->cmd_name);
    for (int i = 0; cmd->args && cmd->args[i]; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    free(cmd->input_redirect);
    free(cmd->output_redirect);
    free(cmd->heredoc_delimiter);
    free(cmd);
}

char *extract_filename(char *start) {
    while (*start == ' ') start++;
    char *end = start;
    while (*end && *end != ' ' && *end != '<' && *end != '>') end++;
    char *filename = strndup(start, end - start);
    return filename;
}

t_command *parse_redirections(char *input) {
    t_command *cmd = init_command();

    char *in_redirect_pos = strchr(input, '<');
    char *out_redirect_pos = strchr(input, '>');
    char *append_redirect_pos = strstr(input, ">>");  // NEW: Check for append redirection
    char *heredoc_redirect_pos = strstr(input, "<<");  // NEW: Check for heredoc redirection

    if (heredoc_redirect_pos) {
        *heredoc_redirect_pos = '\0';
        cmd->heredoc_delimiter = extract_filename(heredoc_redirect_pos + 2);
    }

    if (in_redirect_pos) {
        *in_redirect_pos = '\0';
        cmd->input_redirect = extract_filename(in_redirect_pos + 1);
    }

    if (append_redirect_pos) {  // NEW: Check if append redirection is found
        *append_redirect_pos = '\0';
        cmd->output_redirect = extract_filename(append_redirect_pos + 2);
        cmd->output_type = APPEND;  // Set the output type to append
    }
    else if (out_redirect_pos) {  // Only check if simple redirect if append was not found
        *out_redirect_pos = '\0';
        cmd->output_redirect = extract_filename(out_redirect_pos + 1);
    }

    char *token;
    char *tmp = strdup(input);
    char *rest = tmp;
    int count = 0;

    while ((token = strtok_r(rest, " ", &rest))) {
        if (count == 0) {
            cmd->cmd_name = strdup(token);
        } else {
            cmd->args = realloc(cmd->args, sizeof(char *) * (count + 2));
            cmd->args[count] = NULL; 
            cmd->args[count - 1] = strdup(token);
        }
        count++;
    }

    if (cmd->args) {
        cmd->args[count - 1] = NULL;
    }
    free(tmp);
    return cmd;
}