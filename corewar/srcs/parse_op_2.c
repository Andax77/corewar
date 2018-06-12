/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:55:19 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/12 18:08:24 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			check_op(unsigned char *prog, int i)
{
	int		j;
	int		tmp_ocp;

	j = -1;
	if (g_op_tab[prog[i] - 1].modif_carry == 1)
	{
		while (++j < g_op_tab[prog[i] - 1].nb_params)
		{
			tmp_ocp = (((prog[i + 1] >> (2 * (3 - j))) & 0x3) == 3) ? 4 : \
					(prog[i + 1] >> (2 * (3 - j))) & 0x3;
			if ((tmp_ocp & (g_op_tab[prog[i] - 1].params_type[j])) != tmp_ocp)
				return (ERROR);
		}
	}
	else
		if (prog[i] == 1 && (prog[++i] != 0 || prog[++i] != 0 || prog[++i] != 0\
			|| (prog[++i] <= 0 || prog[i] > 16)))
			return (ERROR);
	return (SUCCESS);
}
