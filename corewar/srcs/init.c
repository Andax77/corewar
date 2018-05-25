/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 22:24:15 by eparisot         ###   ########.fr       */
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
		if (x > 253 && !(x = 0))
			y++;
	}
}

static void	draw_map(t_opt *opt)
{
	int		x;
	int		y;
	char	c[3];

	x = 3;
	y = 2;
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	ft_strcpy(c, (opt->ns) ? "ff\0" : "00\0");
	while (y < 66)
	{
		mvprintw(y, x, c);
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
}

int		init_ncurses(t_opt *opt)
{
	if (initscr())
	{
		start_color();
		init_color(COLOR_CYAN, 500, 500, 500);
		draw_borders();
		draw_map(opt);
		curs_set(0);
		return (SUCCESS);
	}
	return (ERROR);
}

int			init(char **argv, t_cor *cor)
{
	if (init_cor(cor, argv) == ERROR)
		return (ERROR);
	if (cor->opt->n)
	{
		getch();
		endwin();
	}
	return (SUCCESS);
}
