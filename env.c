/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:34:37 by mounali           #+#    #+#             */
/*   Updated: 2023/09/21 17:34:39 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_cmd(char **envp)
{
    int i;
    i = 0;

    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}
