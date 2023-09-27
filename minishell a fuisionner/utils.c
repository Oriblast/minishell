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

static int  ft_count_words(const char *str, char c)
{
    int count;
    int in_substring;

    count = 0;
    in_substring = 0;
    while (*str != '\0')
    {
        if (*str == c)
            in_substring = 0;
        else if (in_substring == 0)
        {
            in_substring = 1;
            count++;
        }
        str++;
    }
    return (count);
}

static char	*ft_make_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
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
	tab = malloc(sizeof(char *) * (words + 1));
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

char    *ft_strjoin(char *path, char *cmd)
{
    char    *full_cmd;
    int     total_length;

	if (!path || !cmd)
    return (NULL);
    
    total_length = ft_strlen(path) + ft_strlen(cmd) + 2;  // +1 pour '/', +1 pour '\0'
    full_cmd = malloc(total_length);
    if (!full_cmd)
        return (NULL);

    ft_strcpy(full_cmd, path);
    ft_strcat(full_cmd, "/");
    ft_strcat(full_cmd, cmd);

    return (full_cmd);
}

char    *ft_strncpy(char *dst, const char *src, size_t len)
{
    size_t  i;

    i = 0;
    while (i < len && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    while (i < len)
    {
        dst[i] = '\0';
        i++;
    }
    return (dst);
}

int	is_empty_string(char *str)
{
	while (*str)
	{
		if (!isspace(*str))  // isspace() vérifie si un caractère est un espace blanc (espace, tabulation, etc.)
			return (0);
		str++;
	}
	return (1);
}


