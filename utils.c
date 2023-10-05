/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:32:32 by mounali           #+#    #+#             */
/*   Updated: 2023/09/25 21:32:44 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_words(const char *str, char c)
{
	int		count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*str)
	{
		if (*str == c)
			in_substring = 0;
		else if (!in_substring)
		{
			in_substring = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	*ft_make_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		words;
	char	**tab;

	if (!str)
		return (NULL);
	words = ft_count_words(str, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			tab[i] = ft_make_word(str, c);
			i++;
			while (*str && *str != c)
				str++;
		}
		else
			str++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strjoin(char *path, char *cmd)
{
	char	*full_cmd;
	int		total_length;

	if (!path || !cmd)
		return (NULL);
	total_length = ft_strlen(path) + ft_strlen(cmd) + 2;
	full_cmd = (char *)malloc(total_length);
	if (!full_cmd)
		return (NULL);
	ft_strcpy(full_cmd, path);
	ft_strcat(full_cmd, "/");
	ft_strcat(full_cmd, cmd);
	return (full_cmd);
}
