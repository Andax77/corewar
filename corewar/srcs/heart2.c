/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:00:49 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/19 11:00:51 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		heart_color(void)
{
	init_pair(26, COLOR_RED, COLOR_RED);
	init_pair(27, COLOR_GREEN, COLOR_GREEN);
	init_pair(28, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(29, COLOR_BLUE, COLOR_BLUE);
}

int			stat_heart(t_cor *cor, t_list *champs, int live)
{
	int		player;
	int		stat;

	stat = 1;
	player = ((t_champ*)champs->content)->id;
	if (((t_champ*)champs->content)->r_cy == -1)
		stat = 4;
	else if (((cor->cycle % cor->cycle_to_die) > (cor->cycle_to_die / 2)) &&
			((t_champ*)champs->content)->live == 0 && (stat = 3))
		((t_champ*)champs->content)->live = 0;
	else if (((cor->cycle % cor->cycle_to_die) > (cor->cycle_to_die / 3)) &&
			((t_champ*)champs->content)->live == 0 && (stat = 2))
		((t_champ*)champs->content)->live = 0;
	else if (((cor->cycle % cor->cycle_to_die) > (cor->cycle_to_die / 4)) &&
			((t_champ*)champs->content)->live == 0 && (stat = 1))
		((t_champ*)champs->content)->live = 0;
	if (live == 10)
	{
		print_heart2(4, player, stat, live);
		attroff(A_BOLD);
	}
	return (stat);
}

void		print_heart(t_cor *cor)
{
	t_list	*champs;
	int		stat;

	champs = cor->champs;
	while (champs)
	{
		stat = stat_heart(cor, champs, 0);
		print_heart2(4, ((t_champ *)champs->content)->id, stat, 0);
		champs = champs->next;
	}
}
