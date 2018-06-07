/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:55:19 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/07 20:21:29 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		check_op_len(t_champ *champ)
{
	int		i;

	i = 0;
	while (i < champ->op_nb)
	{
		if (champ->splited_prog[i] > 16)
			return (ERROR);
		(champ->splited_prog[i] == 1) ? i += 4: 0;
		//TODO all op_codes
		i++;
	}
	return (SUCCESS);
}
