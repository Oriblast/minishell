/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:28:35 by mounali           #+#    #+#             */
/*   Updated: 2023/10/02 20:28:51 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *cmd, char *s, int space)
{
	int	i;

	i = 0;
	while ((s[i] < 9 && s[i] > 13) || (s[i] != ' ' && s[i]))
	{
		if (cmd[i] != s[i])
			return (0);
		i++;
	}
	if (cmd[i] != ' ' && space == 1)
		return (0);
	return (1);
}

void	cwd(void)
{
	char	path[MAX_PATH_SIZE];

	if (getcwd(path, sizeof(path)) == NULL)
		perror("getcwd");
	else
		printf("%s\n", path);
}

int	cdd(char *cmd)
{
	char	*new_path;
	int		offset;

	offset = 3;
	while (cmd[offset] == ' ')
		offset++;
	new_path = cmd + offset;
	if (strlen(new_path) == 0)
		new_path = getenv("HOME");
	if (chdir(new_path) != 0)
		perror("cd");
	return (1);
}
