/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/26 00:01:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		check_champ(t_champ **champ, char *path)
{
	t_list *instru;

	if ((instru = (*champ)->instru))
		while (instru)
			instru = instru->next;
	else
	{
		ft_printf("{red}error : champion '%s' is empty{eoc}\n", path);
		return (ERROR);
	}
	return (SUCCESS);
}
