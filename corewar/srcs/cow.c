/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:56:43 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:56:45 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_cow(t_cor *cor)
{
	static int x;
	static int color;

	if (color == 0 && ++color)
		heart_color();
	attron(COLOR_PAIR(17));
	if (cor->cycle_to_die < 750)
	{
		if (x == 0 && ++x)
			angry_cow1(4);
		else if (x == 1 && ++x)
			angry_cow2(4);
		else if (x == 2 && !(x = 0))
			angry_cow3(4);
	}
	else
	{
		if (x == 0 && ++x)
			draw_cow1(4);
		else if (x == 1 && ++x)
			draw_cow2(4);
		else if (x == 2 && !(x = 0))
			draw_cow3(4);
	}
}

void		heart_color()
{
	init_pair(26, COLOR_RED, COLOR_RED);
	init_pair(27, COLOR_GREEN, COLOR_GREEN);
	init_pair(28, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(29, COLOR_BLUE, COLOR_BLUE);
}

int			stat_heart(int player)
{
	attron(A_BOLD);
	print_heart(4, player, 1);
	attroff(A_BOLD);
	return (1);
}

void		draw_cow1(int nb)
{
	nb = 35 + (4 * (nb - 1));
	draw_line2(nb++, "----------------------------------------------------");
	draw_line2(nb++, "                                                    ");
	draw_line2(nb++, "		    __    ____                               ");
	draw_line2(nb++, "		   /{_\\_/   `'\\____                        ");
	draw_line2(nb++, "		    \\___  (o)  (o   }                       ");
	draw_line2(nb++, "		     /            -'ô                      ");
	draw_line2(nb++, "		     #   \\_    `__\\                       ");
	draw_line2(nb++, "		    ###   \\__ (o'o)                         ");
	draw_line2(nb++, "		   ###    #(  `===='                       ");
	draw_line2(nb++, "		  ####     ##|                           __");
	draw_line2(nb++, "		 ##         ###|                        //");
	draw_line2(nb++, "		 #            #)                       //");
	draw_line2(nb++, "		 |   ###    \\###|_____    //nnnnnnn/--//");
	draw_line2(nb++, "		 |    ###    \\______| |\\ //nnnnnnn/  //");
	draw_line2(nb++, "		 |#    ##           | | //nnnnnnn/  //");
	draw_line2(nb++, "		 |##       \\--------°- //nnnnnnn/  //");
	draw_line2(nb++, "		 |###       ####|     //nnnnnnn/  //");
	draw_line2(nb++, "                              ------------");
	draw_line2(nb++, "			 C.O.W -- W.A.R");
}

void		draw_cow2(int nb)
{
	nb = 35 + (4 * (nb - 1));
	draw_line2(nb++, "----------------------------------------------------");
	draw_line2(nb++, "                                                    ");
	draw_line2(nb++, "		    __    ____                               ");
	draw_line2(nb++, "		   /{_\\_/   `'\\____                      ");
	draw_line2(nb++, "		    \\___  (o)  (o   }                      ");
	draw_line2(nb++, "		     /            -'ô                      ");
	draw_line2(nb++, "		     #   \\_    `__\\                      ");
	draw_line2(nb++, "		    ###   \\__ (o'o)                         ");
	draw_line2(nb++, "		   ###    #(  `===='                         ");
	draw_line2(nb++, "		  ####     ##|      ______               __");
	draw_line2(nb++, "		 ##         ###|  //   |___|            //");
	draw_line2(nb++, "		 #            #)_//    |___|           //");
	draw_line2(nb++, "		 |   ###              //  //nnnnnnn/--//");
	draw_line2(nb++, "		 |    ###      ______//  //nnnnnnn/  //");
	draw_line2(nb++, "		 |#    ##       |       //nnnnnnn/  //");
	draw_line2(nb++, "		 |##            |      //nnnnnnnn/  //");
	draw_line2(nb++, "		 |###       ####|     //nnnnnnn/  //");
	draw_line2(nb++, "                              ------------");
	draw_line2(nb++, "			 C.O.W -- W.A.R");
}

void		draw_cow3(int nb)
{
	nb = 35 + (4 * (nb - 1));
	draw_line2(nb++, "----------------------------------------------------");
	draw_line2(nb++, "                                                    ");
	draw_line2(nb++, "		    __    ____                               ");
	draw_line2(nb++, "		   /{_\\_/   `'\\____                       ");
	draw_line2(nb++, "		    \\___  (o)  (o   }                      ");
	draw_line2(nb++, "		     /            -'ô                       ");
	draw_line2(nb++, "		     #   \\_    `__\\                      ");
	draw_line2(nb++, "		    ###   \\__ (o'o)                        ");
	draw_line2(nb++, "		   ###    #(  `===='                        ");
	draw_line2(nb++, "		  ####     ##|                           __");
	draw_line2(nb++, "		 ##         ###|                        //");
	draw_line2(nb++, "		 #            #)\\_____________         //");
	draw_line2(nb++, "		 |   ###     ###|\\_________|_ |nnnn/--//");
	draw_line2(nb++, "		 |    ###               |  |nnnnnn/  //");
	draw_line2(nb++, "		 |#    ##       \\_______|__|nnnnn/  //");
	draw_line2(nb++, "		 |##                   //nnnnnnnn/  //");
	draw_line2(nb++, "		 |###       ####|     //nnnnnnn/  //");
	draw_line2(nb++, "                              ------------");
	draw_line2(nb++, "			 C.O.W -- W.A.R");
}
