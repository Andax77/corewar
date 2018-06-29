/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:57:09 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/29 09:57:08 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_heart2(int player, int stat)
{
	if (stat == 1)
		stat1(player);
	if (stat == 2)
		stat2(player);
	if (stat == 3)
		stat3(player);
	if (stat == 4)
		stat4(player);
}

void		stat1(int player)
{
	int		nb;

	nb = 41;
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

void		stat2(int player)
{
	int		nb;

	nb = 41;
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

void		stat3(int player)
{
	int		nb;

	nb = 41;
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

void		stat4(int player)
{
	int		nb;

	nb = 41;
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
