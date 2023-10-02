/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:23:12 by mounali           #+#    #+#             */
/*   Updated: 2023/10/01 20:23:23 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n && (*us1 || *us2))
	{
		if (*us1 != *us2)
			return (*us1 - *us2);
		us1++;
		us2++;
		n--;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char		*next_token = NULL;
	char			*token_start;

	if (str)
		next_token = str;
	if (!next_token)
		return (NULL);
	while (*next_token && strchr(delim, *next_token))
		next_token++;
	if (!*next_token)
		return (NULL);
	token_start = next_token;
	while (*next_token && !strchr(delim, *next_token))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	return (token_start);
}
