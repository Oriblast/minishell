/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:30 by ksongbe           #+#    #+#             */
/*   Updated: 2023/09/21 21:59:27 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_child_pid = -1;

int	check(char *cmd, char *s, int space)
{
	int i;
	i = 0;

	while ((s[i] < 9 && s[i] > 13) || s[i] != ' ' && s[i])
	{
		if (cmd[i] != s[i])
			return (0);
		i++;
	}
	if (cmd[i] != ' ' && space == 1)
		return (0);
	return (1);
}

void	cwd(char *path)
{
	getcwd(path, sizeof(path));
	if (path == NULL)
		perror("getcwd");
	else
		printf("%s\n", path);
}

int	cdd(char *cmd, char *path)
{
	char	path2[5000];
	int		i;
	int		j;
	int		k;
	int		pp;
	int		p[10][1];
	char	path3[5000];

	i = 0;
	pp = 0;
	while (path[i])
	{
		if (path[i] == '/' && i != 0)
		{
			p[pp][0] = i;
			pp++;
		}
		path2[i] = path[i];
		i++;
	}
	j = i;
	i = 0;
	while (cmd[i] != 'd')
		i++;
	i++;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
	{
		chdir("/home");
		return (0);
	}
	if (cmd[i] == '/')
	{
		j = 0;
		while(cmd[i])
		{
			path[j] = cmd[i];
			i++;
			j++;
		}
		path[j] = 0;
		//if (path2[j - 1] == '/')
		//	path2[j - 1] = 0;
		if (chdir(path) != 0)
		{
			printf("cd: no such file or directory");
			i = 0;
			while (path2[i])
			{
				path[i] = path2[i];
				i++;
			}
			path[i] = 0;
		}
		return (1);
	}
	if (cmd[i] == '.' && cmd[i + 1] == '.')
	{
		if (pp == 0 && path[1] != '\0')
		{
			path[1] = 0;
			chdir(path);
			return(1);
		}
		else if (pp == 0 && path[1] == '\0')
			return (1);
		else
		{
			printf("%c\n",path[p[pp - 1][0] + 1]);
			if (path[p[pp - 1][0] + 1] == '\0')
			{
				if (pp > 1)
					path[p[pp - 2][0]] = 0;
				else
					path[1] = 0;
			}
			else
				path[p[pp - 1][0]] = 0;
			chdir(path);
		}
		return (1);
	}
	k = 0;
	while (cmd[i])
	{
		path3[k] = cmd[i];
		k++;
		i++;
	}
	path3[k] = 0;
	printf("path3 = %s et cmd = %s",path3, cmd);
	i = 0;
	while (path3[i])
	{
		path2[j] = path3[i];
		i++;
		j++;
	}
	path2[j] = 0;
	printf("path2 = %s", path2);
	if (chdir(path2) != 0)
		printf("cd: no such file or directory %s", path3);
	else
	{
		i = 0;
		while (path2[i])
		{
			path[i] = path2[i];
			i++;
		}
		path[i] = 0;

	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		j;
	int		x;
	char	*cmd;
	char	path[5000];
	char	*ptr;
	char	*s1;

	i = 1;
	x = 1;
	chdir("/home");
	setup_signals();
	rl_bind_keyseq("\\C-\\", rl_insert); // Bind Ctrl+\ to do nothing

	struct termios oldt, newt;

	while (i)
	{
		if (x)
		{
		//	cwd(path);
		tcgetattr(STDIN_FILENO, &oldt);  // obtenir les paramètres actuels
    	newt = oldt;
    	newt.c_lflag &= ~ECHOCTL;       // désactiver l'écho pour les signaux de contrôle
    	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
			cmd = readline("$> ");
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Remettez les choses en ordre après avoir lu l'entrée
			if (!cmd)
			{
				printf("\n");
				return(0);
			}
			add_history(cmd);
			if (is_empty_string(cmd))
			{
				free(cmd);
				continue;  // si la commande est vide, revenez au début de la boucle pour attendre une nouvelle entrée
			}
			x = 0;
		}
		if (!cmd)
			break;
		
		else if (check(cmd, "cd", 0) == 1)
		{
			ptr = path;
			cdd(cmd, ptr);
			x = 1;
		}
		else if(check(cmd, "pwd", 0) == 1)
		{
			cwd(path);
			x = 1;
		}
		else if(check(cmd, "echo", 0) == 1)
		{
			echo_cmd(cmd, env);
			x = 1;
		}
		else if (check(cmd, "env", 0) == 1)
		{
			env_cmd(env);
			x = 1;
		}
		else if (check(cmd, "unset", 1) == 1)
		{
			char	*varname = cmd + 6;
			while (*varname == ' ')
				varname++;
			unset_cmd(env, varname);
			x = 1;
		}
        else if (strcmp(cmd, "exit") == 0)
        {
            printf("Merci d'avoir utilisé notre mini-shell ! Au revoir !\n");
            rl_clear_history();
            exit(0);
        }
		else if (check(cmd, "export", 0) == 1)
		{
			export_cmd(cmd + 7, &env);
			x = 1;
		}
		else if (ft_strstr(cmd, "|") != NULL)
		{
			execute_with_pipes(cmd, env);
			x = 1;
		}
		else
		{
			char	**split_cmd = ft_split(cmd, ' ');
			char	*full_cmd_path = find_cmd_in_path(split_cmd[0], env); // cherche le chemin complet dans PATH

			if (full_cmd_path)
			{
				char *args[] = {full_cmd_path, NULL};
				execute_extern_cmd(full_cmd_path, split_cmd, env); // execute avec le chemin complet
				free(full_cmd_path);
				x = 1;
			}
			else
			{
				printf("minishell: %s: command not found\n", split_cmd[0]);
				x = 1;
			}
			free_str_array(split_cmd);
		}
		x = 1;
		free(cmd);
	}
	return (0);
}
