/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:57:09 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:57:11 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		heart(int nb, int player, int stat)
{
	attron(17);
	if (stat == 1)
		stat1(nb, player);
	if (stat == 2)
		stat2(nb, player);
	if (stat == 3)
		stat3(nb, player);
	if (stat == 4)
		stat4(nb, player);
}

void		stat1(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0);
	draw_heart(nb, player, "**", 3);
	draw_heart(nb, player, " ", 5);
	draw_heart(nb, player, "**", 6);
	draw_heart(nb++, player, "   ", 8);
	draw_heart(nb, player, "  ", 0);
	draw_heart(nb, player, "*******", 2);
	draw_heart(nb++, player, "  ", 9);
	draw_heart(nb, player, "   ", 0);
	draw_heart(nb, player, "*****", 3);
	draw_heart(nb++, player, "   ", 8);
	draw_heart(nb, player, "    ", 0);
	draw_heart(nb, player, "***", 4);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb, player, "     ", 0);
	draw_heart(nb, player, "*", 5);
	draw_heart(nb++, player, "     ", 6);
}

void		stat2(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0);
	draw_heart(nb, player, "**", 3);
	draw_heart(nb, player, " ", 5);
	draw_heart(nb, player, "*", 6);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb, player, "  ", 0);
	draw_heart(nb, player, "*****", 2);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb, player, "    ", 0);
	draw_heart(nb, player, "**", 3);
	draw_heart(nb, player, "  ", 5);
	draw_heart(nb, player, "*", 7);
	draw_heart(nb++, player, "   ", 8);
	draw_heart(nb, player, "    ", 0);
	draw_heart(nb, player, "**", 4);
	draw_heart(nb++, player, "     ", 6);
	draw_heart(nb, player, "     ", 0);
	draw_heart(nb, player, "*", 5);
	draw_heart(nb++, player, "     ", 6);
}

void		stat3(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0);
	draw_heart(nb, player, "**", 3);
	draw_heart(nb++, player, "      ", 5);
	draw_heart(nb, player, "    ", 0);
	draw_heart(nb, player, "***", 4);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb, player, "     ", 0);
	draw_heart(nb, player, "**", 5);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb, player, "     ", 0);
	draw_heart(nb, player, "*", 5);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb++, player, "           ", 0);
}

void		stat4(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb++, player, "           ", 0);
	draw_heart(nb, player, "    ", 0);
	draw_heart(nb, player, "IS", 4);
	draw_heart(nb++, player, "     ", 6);
	draw_heart(nb++, player, "           ", 0);
	draw_heart(nb, player, "   ", 0);
	draw_heart(nb, player, "DEAD", 3);
	draw_heart(nb++, player, "    ", 7);
	draw_heart(nb++, player, "           ", 0);
}
