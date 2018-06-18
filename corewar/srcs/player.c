/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:56:59 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:57:00 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_player(int nb, int player)
{
	int x;

	attron(COLOR_PAIR(17));
	x = nb;
	while (player)
	{
		nb = 26 + (4 * (x - 1));
		draw_line2(nb++, "---------------------------------------------------");
		draw_player(nb++, player, " __Player __ ");
		mvprintw(39, 209 + player * 14 - 14 - player, ft_itoa(player));
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

	if (i > 10)
		i -= 10;
	id = y;
	x = 201 + y * 14 - 14 - y + i;
	y = 30;
	while (y < 66)
	{
		if (line_idx == y)
		{
			if (ft_strchr(line, ' '))
				attron(COLOR_PAIR(17));
			else if (ft_strstr(line , "IS") || ft_strstr(line, "DEAD"))
				attron(COLOR_PAIR(2 + id));
			else
				attron(COLOR_PAIR(id + 25));
			mvprintw(y, x, line);
		}
		y++;
	}
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
