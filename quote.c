 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:15:44 by ksongbe           #+#    #+#             */
/*   Updated: 2023/09/23 21:15:48 by ksongbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int checkstar(char *cmd)
{
	int i;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int check2(char *buff2, char *args, int k, int j, char *buff3)
{
	while (k > 1)
	{
		if (buff2[j] != args[k])
			return (0);
		k--;
		j--;
	}
	k = 0;
	j = 0;
	if (buff3[0] != 0)
	{
		while (buff3[k])
			k++;
	}
	while (buff2[j])
	{
		buff3[k] = buff2[j];
		k++;
		j++;
	}
	buff3[k] = ' ';
	k++;
	buff3[k] = 0;
	return (1);
}

void	re(char *buff, char **args2, char *buff2, char *buff3, char **args)
{
	int	i;
	int j;
	int	k;

	i = 0;
	if (args2[1][0] == '*' && args2[1][1] != '\0' && args2[1][1] != ' ')
	{
		j = 0;
	while (args2[1][j])
		j++;
	k = j;
	j = 0;
	while (args[0][i])
	{
		buff3[j] = args[0][i];
		i++;
		j++;
	}
	buff3[j] = ' ';
	j++;
	buff3[j] = 0;
	i = 0;
	j = 0;
		while (buff[i])
		{
			if (buff[i] != '\n' && buff[i] != '\0')
			{
				buff2[j] = buff[i];
				j++;
			}
			if (buff[i] == '\n')
			{
				buff2[j] = 0;
				check2(buff2, args2[1], k, j, buff3);
				j = 0;
			}
			i++;
		}
	}
}

void	exe(char **args, char **env)
{
	pid_t	pid;
	int		status;
	//int		retour;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
        exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if ((status & 0xFF) == 0)
			all_retour(status);
	}
}

int star(char *cmd, char **env)
{
    pid_t	pid;
    int		fd;
    int		save;
    int		status;
    char	**args;
	char	**args2;
	char	buff[100000];
	int		r2;
	//int		r1;
	char	buff2[1000];
	char	buff3[1000];


	r2 = 1;
    save = dup(STDOUT_FILENO);
    args = ft_split("/bin/ls", ' ');
	args2 = ft_split(cmd, ' ');
    if (!args)
    {
        perror("ft_split");
        exit(EXIT_FAILURE);
    }
    fd = open(".tempss", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
		if (args2[0][0] != '/')
			printf("/bin/%s\n", args2[0]);
		else
			printf("%s\n", args2[0]);
        if (execve("/bin/ls", args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        close(fd);
        fd = open(".tempss", O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
	if ((status & 0xFF) == 0)
	{

		r2 = read(fd, buff, 10000);
		free_str_array(args);
		buff[r2] = '\0';
		//r1 = 0;
	//	printf("buff = %s", buff);
		args = ft_split(buff, '\n');
		//printf("ok%sok\n %s\n", args[0], args[1]);

	if (args2[1][0] == '*' && args2[1][1] == 0)
		exe(args, env);
	else
	{
		re(buff, args2, buff2, buff3, args);
		//printf("%s", buff);
		exe(ft_split(buff3, ' '), env);
	}
	free_str_array(args);
	close(fd);
    }
    dup2(save, STDOUT_FILENO);
	}
    return (1);
}