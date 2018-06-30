/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:00:49 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/30 00:06:31 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		heart_color(void)
{
	init_pair(26, COLOR_RED, COLOR_RED);
	init_pair(27, COLOR_GREEN, COLOR_GREEN);
	init_pair(28, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(29, COLOR_BLUE, COLOR_BLUE);
	init_pair(30, COLOR_WHITE, COLOR_WHITE);
}

int			stat_heart(t_cor *cor, t_list *champs)
{
	int		stat;

	stat = 1;
	if (((t_champ*)champs->content)->r_cy == -1)
		stat = 4;
	else if (cor->v_cycle > (3 * (cor->cycle_to_die / 4)))
		stat = 3;
	else if (cor->v_cycle > (cor->cycle_to_die / 2))
		stat = 2;
	else if (cor->v_cycle > (cor->cycle_to_die / 4))
		stat = 1;
	return (stat);
}

void		print_heart(t_cor *cor)
{
	t_list	*champs;
	int		stat;

	champs = cor->champs;
	while (champs)
	{
		if (((t_champ*)champs->content)->father == 0)
		{
			stat = stat_heart(cor, champs);
			print_heart2(((t_champ *)champs->content)->id, stat);
		}
		champs = champs->next;
	}
}
