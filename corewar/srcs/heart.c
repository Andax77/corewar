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

void		print_heart2(int nb, int player, int stat, int live)
{
	if (stat == 1)
		stat1(nb, player, live);
	if (stat == 2)
		stat2(nb, player, live);
	if (stat == 3)
		stat3(nb, player, live);
	if (stat == 4)
		stat4(nb, player, live);
}

void		stat1(int nb, int player, int live)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0 + live);
	draw_heart(nb, player, "**", 3 + live);
	draw_heart(nb, player, " ", 5 + live);
	draw_heart(nb, player, "**", 6 + live);
	draw_heart(nb++, player, "   ", 8 + live);
	draw_heart(nb, player, "  ", 0 + live);
	draw_heart(nb, player, "*******", 2 + live);
	draw_heart(nb++, player, "  ", 9 + live);
	draw_heart(nb, player, "   ", 0 + live);
	draw_heart(nb, player, "*****", 3 + live);
	draw_heart(nb++, player, "   ", 8 + live);
	draw_heart(nb, player, "    ", 0 + live);
	draw_heart(nb, player, "***", 4 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb, player, "     ", 0 + live);
	draw_heart(nb, player, "*", 5 + live);
	draw_heart(nb++, player, "     ", 6 + live);
}

void		stat2(int nb, int player, int live)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0 + live);
	draw_heart(nb, player, "**", 3 + live);
	draw_heart(nb, player, " ", 5 + live);
	draw_heart(nb, player, "*", 6 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb, player, "  ", 0 + live);
	draw_heart(nb, player, "*****", 2 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb, player, "    ", 0 + live);
	draw_heart(nb, player, "**", 3 + live);
	draw_heart(nb, player, "  ", 5 + live);
	draw_heart(nb, player, "*", 7 + live);
	draw_heart(nb++, player, "   ", 8 + live);
	draw_heart(nb, player, "    ", 0 + live);
	draw_heart(nb, player, "**", 4 + live);
	draw_heart(nb++, player, "     ", 6 + live);
	draw_heart(nb, player, "     ", 0 + live);
	draw_heart(nb, player, "*", 5 + live);
	draw_heart(nb++, player, "     ", 6 + live);
}

void		stat3(int nb, int player, int live)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb, player, "   ", 0 + live);
	draw_heart(nb, player, "**", 3 + live);
	draw_heart(nb++, player, "      ", 5 + live);
	draw_heart(nb, player, "    ", 0 + live);
	draw_heart(nb, player, "***", 4 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb, player, "     ", 0 + live);
	draw_heart(nb, player, "**", 5 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb, player, "     ", 0 + live);
	draw_heart(nb, player, "*", 5 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb++, player, "           ", 0 + live);
}

void		stat4(int nb, int player, int live)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb++, player, "           ", 0 + live);
	draw_heart(nb, player, "    ", 0 + live);
	draw_heart(nb, player, "IS", 4 + live);
	draw_heart(nb++, player, "     ", 6 + live);
	draw_heart(nb++, player, "           ", 0 + live);
	draw_heart(nb, player, "   ", 0 + live);
	draw_heart(nb, player, "DEAD", 3 + live);
	draw_heart(nb++, player, "    ", 7 + live);
	draw_heart(nb++, player, "           ", 0 + live);
}
