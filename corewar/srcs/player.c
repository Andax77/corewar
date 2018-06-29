/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:56:59 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/29 09:52:15 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_player(int player)
{
	int		nb;

	attron(COLOR_PAIR(17));
	while (player)
	{
		nb = 38;
		draw_line2(nb++, "---------------------------------------------------");
		draw_player(nb++, player, " ___________ ");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|           |");
		draw_player(nb++, player, "|___________|");
		player--;
	}
}

void		draw_heart(int line_idx, int y, char *line, int i)
{
	int		x;
	int		id;

	id = y;
	x = 201 + y * 14 - 14 - y + i;
	y = 30;
	while (y < 66)
	{
		if (line_idx == y)
		{
			get_color_heart(0, line, id);
			mvprintw(y, x, line);
		}
		y++;
	}
}

void		get_color_heart(int draw_live, char *line, int id)
{
	static int live[4];

	if (live[id] >= 1)
	{
		if (ft_strchr(line, ' '))
			attron(COLOR_PAIR(17));
		else if (ft_strstr(line, "IS") || ft_strstr(line, "DEAD"))
			attron(COLOR_PAIR(2 + id));
		else
			attron(COLOR_PAIR(30));
		live[id]--;
	}
	else
	{
		if (ft_strchr(line, ' '))
			attron(COLOR_PAIR(17));
		else if (ft_strstr(line, "IS") || ft_strstr(line, "DEAD"))
			attron(COLOR_PAIR(2 + id));
		else
			attron(COLOR_PAIR(id + 25));
	}
	if (draw_live == 1)
		live[id] = 16;
}

void		draw_player(int line_idx, int y, char *line)
{
	int		x;

	x = 200 + y * 14 - 14 - y;
	y = 30;
	while (y < 66)
	{
		if (line_idx == y)
			mvprintw(y, x, line);
		y++;
	}
}

void		draw_line2(int line_idx, char *line)
{
	int		x;
	int		y;

	x = 199;
	y = 2;
	while (y < 66)
	{
		if (line_idx == y)
			mvprintw(y, x, line);
		y++;
	}
}
