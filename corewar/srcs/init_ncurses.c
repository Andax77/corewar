/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/03 12:52:13 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	draw_borders(void)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < 68)
	{
		if (y == 0 || y == 67 || x == 0 || x == 196 || x == 253)
			mvprintw(y, x, "*");
		x++;
		if (x > 253 && !(x = 0))
			y++;
	}
}

void	draw_map(t_cor *cor)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		attron(COLOR_PAIR(cor->c_map[i]));
		draw_uchar(i, cor->map[i]);
	}
}

void	draw_infos(t_list *champs, int nb)
{
	int		id;

	id = 1;
	draw_line(2, 0, "** PAUSED **");
	draw_line(4, 0, "Cycles/second limit : 50");
	draw_line(7, 0, "Cycle :");
	draw_line(9, 0, "Processes :");
	while (get_v_ids(champs, id++, &nb) != count_champs(champs) + 1)
		;
	draw_line(27, 0, "CYCLES_TO_DIE :         /");
	draw_line(30, 0, "CYCLE_DELTA :");
	draw_line(32, 0, "NBR_LIVE :");
	draw_line(34, 0, "MAX_CHECKS :");
}

void	init_colors(t_list *champs)
{
	t_list	*tmp;
	int		i;

	tmp = champs;
	while (champs)
	{
		i = ((t_champ*)champs->content)->id;
		init_pair(i + 2, COLOR_BLACK + i, COLOR_BLACK);
		champs = champs->next;
	}
	champs = tmp;
	while (champs)
	{
		i = ((t_champ*)champs->content)->id;
		init_pair(i + 20, COLOR_BLACK, i);
		champs = champs->next;
	}
	champs = tmp;
	while (champs)
	{
		i = ((t_champ*)champs->content)->id;
		init_pair(i + 40, 17, i);
		champs = champs->next;
	}
}

void	init_special_colors(void)
{
	init_color(COLOR_MAGENTA, 500, 500, 500);
	init_color(17, 1000, 1000, 1000);
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(17, 17, COLOR_BLACK);
}
