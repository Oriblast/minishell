/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:00:55 by mounali           #+#    #+#             */
/*   Updated: 2023/10/25 20:52:33 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <stddef.h>

# define MAX_SEGMENTS	10
# define MAX_PATH_SIZE	1024
# define NORMAL			0
# define APPEND			1

extern pid_t		g_child_pid;
extern int			g_last_return_code;

typedef struct s_command
{
	char			*cmd_name;
	char			**args;
	char			*input_redirect;
	char			*output_redirect;
	int				output_type;
	char			*heredoc_delimiter;
	int				retour;
}					t_command;

typedef struct s_vari
{
	char			*cmd2;
	int				*car;	
	int				k;
}					t_vari;

typedef struct s_subcommand
{
	char			*cmd_name;
	char			**args;
	char			*input_redirect;
	char			*output_redirect;
}					t_subcommand;

int				check(char *cmd, char *s, int space);
void			echo_cmd(t_command *cmd, char **envp);
void			env_cmd(char **envp);
void			unset_cmd(char **envp, char *varname);
char			**export_cmd(char *command, char ***envp);
void			execute_extern_cmd(t_command *cmd, char **envp);
void			setup_signals(void);
void			execute_cmd_with_path(char *cmd, char **args, char **envp);
char			*find_cmd_in_path(char *cmd, char **envp);
void			redirect_input(char *filename);
void			redirect_output(char *filename);
void			redirect_append(char *filename);
int				cdd(char *cmd);
int				ft_put_err(char *err, char *desc, int ret);
int				ft_create_fd_pipe(int cmd_count, int **fd);
int				ft_pipe(int cmd_count, char ***cmds);
int				parse_echo_flags(char *line, int *i);
void			print_between_quotes(char *line, int *i, char **envp);
void			handle_var_substitution(char *line, int *i, char **envp);
void			ft_putchar_fd(char c, int fd);
void			execute_helper(pid_t pid, char *cmd, char **args, char **envp);
char			*get_path_from_envp(char **envp);
void			terminal_setup(void);
char			**execute_command(char *cmd_input, char **env, t_vari *a);
void			cwd(void);
int				index_env(char *name, char **envp);
char			*ft_strjoin(char *path, char *cmd);
char			**ft_split(const char *str, char c);
size_t			ft_strlen(const char *s);
void			free_str_array(char **strs);
int				is_empty_string(char *str);
char			*ft_strtok(char *str, const char *delim);
char			*strchr(const char *s, int c);
char			*trim_space(char *str);
char			*ft_strcat(char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strstr(const char *haystack, const char *needle);
int				count_str_array(char **array);
char			**my_completion(const char *text, int start);
char			*ft_strncpy(char *dst, const char *src, size_t len);
void			ft_putendl_fd(char *s, int fd);
void			free_str_array(char **strs);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strchr(const char *s, int c);
void			execute_single_command_in_pipe(char *cmd, int *read_fd,
					int *write_fd, char **env);
void			free_pipe_memory(int num_cmds, int **pipes);
void			close_pipe_fds(int num_cmds, int **pipes);
void			initialize_pipes(int num_cmds, int ***pipes);
void			child_processes(char *cmd, int *read_fd,
					int *write_fd, char **env);
void			fork_process(char **args, char *full_cmd_path, char **env);
void			execute_pipe_command(char **cmds, char **env);
t_command		*parse_redirections(char *input);
t_command		*parse_redirections(char *input);
char			*extract_filename(char *start);
void			free_command1(t_command *cmd);
t_command		*init_command(void);
void			execute_with_redirections(t_command *cmd, char **env);
void			free_command(t_command *cmd);
void			handle_external_command(t_command *cmd, char **env);
char			**construct_args_for_execve(t_command *cmd, char **envp,
					int include_full_path_as_arg);
void			handle_heredoc(t_command *cmd);
char			*create_heredoc_file(const char *delimiter);
t_subcommand	**split_into_subcommands(const char *cmd_input);
char			**extract_args(const char *input);
void			handle_redirection(const char *token, t_subcommand *subcmd);
t_command		**parse_subcommands_with_redirections(const char *cmd_input);
void			execute_pipelines(t_command **commands, char **envp);
void			free_subcommands(t_subcommand **subcommands);
char			*trim(char *str);
t_command		*convert_subcommand_to_command(t_subcommand *subcmd);
void			free_command(t_command *cmd);
void			free_commands(t_command **commands);
//void			all_retour(int *retour, int *status);
void			clean_heredoc(t_command *cmd);

int				count_commands(t_command **commands);
void			create_pipes(int num_cmds, int pipe_fds[][2]);
void			setup_child_process(int i, int num_cmds,
					int pipe_fds[][2], t_command **commands, char **envp);
void			close_pipes(int num_cmds, int pipe_fds[][2]);
void			handle_redirections(t_command *cmd);
void			close_pipes_and_wait(int num_cmds, int pipe_fds[10][2]);
int				find_command_index(t_command **commands, t_command *cmd);
t_subcommand	fn2a_init_subcmd(char *trimmed_command);
t_command		**fn1_init_commands_array(int num_subcmds);
void			fn2_fill_commands(t_command **commands,
					char **pipe_splits, int num_subcmds);
void			fn2b_handle_memory_errors(t_subcommand *subcmd,
					t_command *command);
int				fn1_count_subcommands(char **pipe_splits);
void			fn2_handle_input_redirection(t_subcommand *subcmd,
					char *trimmed_command);
void			fn3_handle_output_redirection(t_subcommand *subcmd,
					char *trimmed_command);
t_command		*traiter_arguments(char *input, t_command *cmd);
t_command		*traiter_heredoc(char *input, t_command *cmd);
t_command		*init_command_redirection(char *input, t_command *cmd);

char			*get_command_path(t_command *cmd, char **envp);
char			**prepare_args(t_command *cmd, char **envp);
void			all_retour(int status);
void			quote2(char	*cmd, t_vari *a);
int				quote3(char *cmd, int i, char c, t_vari *a);
void			verified(t_vari *a, char *cmd);

int check2(char *buff2, char *args, int k, int j, char *buff3);
void	re(char *buff, char **args2, char *buff2, char *buff3, char **args);
void	exe(char **args, char **env);
int star(char *cmd, char **env);
int checkstar(char *cmd);
char		*ft_itoa(int n);


#endif
