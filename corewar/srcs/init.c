/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/23 17:25:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		init_ncurse()
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	initscr();
	start_color();
	init_color(COLOR_CYAN, 500, 500, 500);
	init_pair(1, COLOR_CYAN, COLOR_CYAN);
	attron(COLOR_PAIR(1));
	while (y < 68)
	{
		if (y == 0 || y == 67 || x == 0 || x == 196 || x == 253)
			mvprintw(y, x, "*");
		x++;
		if (x > 254 && !(x = 0))
			y++;
	}
	x = 3;
	y = 2;
	refresh();
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	while (y < 66)
	{
		mvprintw(y, x, "00");
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
	curs_set(0);
	return (SUCCESS);
}

int		init(t_opt *opt)
{
	if (opt->n)
		if (!init_ncurse())
		{
			return (ERROR);
		}
	getch();
	endwin();
	return (SUCCESS);
}
