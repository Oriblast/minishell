/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allretour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongbe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:24:46 by ksongbe           #+#    #+#             */
/*   Updated: 2023/10/24 01:23:49 by mounali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_retour(int *retour, int *status)
{
	if ((*status & 0xFF) == 0)
		*retour = (*status >> 8) & 0xFF;
}
