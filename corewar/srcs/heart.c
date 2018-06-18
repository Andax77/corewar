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
	draw_heart(nb++, player, "|   ** **   |");
	draw_heart(nb++, player, "|  *******  |");
	draw_heart(nb++, player, "|   *****   |");
	draw_heart(nb++, player, "|    ***    |");
	draw_heart(nb++, player, "|     *     |");
}

void		stat2(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb++, player, "|   ** *    |");
	draw_heart(nb++, player, "|  *****    |");
	draw_heart(nb++, player, "|   **  *   |");
	draw_heart(nb++, player, "|    **     |");
	draw_heart(nb++, player, "|     *     |");
}

void		stat3(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb++, player, "|   **      |");
	draw_heart(nb++, player, "|    ***    |");
	draw_heart(nb++, player, "|     **    |");
	draw_heart(nb++, player, "|     *     |");
	draw_heart(nb++, player, "|           |");
}

void		stat4(int nb, int player)
{
	nb = 29 + (4 * (nb - 1));
	draw_heart(nb++, player, "|           |");
	draw_heart(nb++, player, "|    IS     |");
	draw_heart(nb++, player, "|           |");
	draw_heart(nb++, player, "|   DEAD    |");
	draw_heart(nb++, player, "|           |");
}
