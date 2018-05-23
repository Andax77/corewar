/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/23 18:12:25 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	draw_borders(void)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
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
}

static void	draw_map(void)
{
	int		x;
	int		y;
	
	x = 3;
	y = 2;
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	while (y < 66)
	{
		mvprintw(y, x, "00");
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
}

static void		init_ncurse(void)
{
	initscr();
	start_color();
	init_color(COLOR_CYAN, 500, 500, 500);
	draw_borders();
	draw_map();
	curs_set(0);
}

int		init(t_opt *opt)
{
	if (opt->n)
		if (!init_ncurse())
			return (ERROR);
	getch();
	endwin();
	return (SUCCESS);
}
