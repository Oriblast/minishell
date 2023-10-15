/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:00:55 by mounali           #+#    #+#             */
/*   Updated: 2023/10/15 23:44:56 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SEGMENTS 10
# define MAX_PATH_SIZE 1024

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

extern pid_t	g_child_pid;


typedef	struct s_vari
{
	char	*cmd2;
	int		*car;	
}t_vari;

typedef struct s_pipe_info
{
	int			i;
	int			num_cmds;
	char		**cmds;
	int			**pipes;
	char		**env;
	int			*cur_read_fd;
	int			*cur_write_fd;
}				t_pipe_info;

int		check(char *cmd, char *s, int space);
void	echo_cmd(char *line, char **envp);
void	env_cmd(char **envp);
void	unset_cmd(char **envp, char *varname);
char	**export_cmd(char *command, char ***envp);
void	execute_extern_cmd(char *cmd, char **args, char **envp,
			int should_fork);
void	setup_signals(void);
void	execute_cmd_with_path(char *cmd, char **args, char **envp);
char	*find_cmd_in_path(char *cmd, char **envp);
char	**parse_redirections(char *cmd);
void	redirect_input(char *filename);
void	redirect_output(char *filename);
void	redirect_append(char *filename);
int		cdd(char *cmd);
int		ft_put_err(char *err, char *desc, int ret);
int		ft_create_fd_pipe(int cmd_count, int **fd);
int		ft_pipe(int cmd_count, char ***cmds);
int		parse_echo_flags(char *line, int *i);
void	print_between_quotes(char *line, int *i, char **envp);
void	handle_var_substitution(char *line, int *i, char **envp);
void	ft_putchar_fd(char c, int fd);
void	execute_helper(pid_t pid, char *cmd, char **args, char **envp);
char	*get_path_from_envp(char **envp);
void	terminal_setup(void);
char	**execute_command(char *cmd, char **env);
void	cwd(void);
int		index_env(char *name, char **envp);

char	*ft_strjoin(char *path, char *cmd);
char	**ft_split(const char *str, char c);
size_t	ft_strlen(const char *s);
void	free_str_array(char **strs);
int		is_empty_string(char *str);
char	*ft_strtok(char *str, const char *delim);
char	*strchr(const char *s, int c);
char	*trim_space(char *str);
char	*ft_strcat(char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strstr(const char *haystack, const char *needle);
int		count_str_array(char **array);
char	**my_completion(const char *text, int start);
char	*ft_strncpy(char *dst, const char *src, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	free_str_array(char **strs);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);

void	handle_pipe_execution(t_pipe_info *info);
void	execute_single_command_in_pipe(char *cmd, int *read_fd,
			int *write_fd, char **env);
void	free_pipe_memory(int num_cmds, int **pipes);
void	close_pipe_fds(int num_cmds, int **pipes);
void	initialize_pipes(int num_cmds, int ***pipes);
void	child_processes(char *cmd, int *read_fd, int *write_fd, char **env);
void	fork_process(char **args, char *full_cmd_path, char **env);
void	execute_pipe_command(char **cmds, char **env);
void	set_read_write_fd(t_pipe_info *info);

#endif
