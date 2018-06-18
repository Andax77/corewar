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
	draw_line2(nb++, "		 |##       \\--------°- //nnnnnn/  //");
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
	draw_line2(nb++, "		 |##            |      //nnnnnnn/  //");
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
	draw_line2(nb++, "		 |##                   //nnnnnnn/  //");
	draw_line2(nb++, "		 |###       ####|     //nnnnnnn/  //");
	draw_line2(nb++, "                              ------------");
	draw_line2(nb++, "			 C.O.W -- W.A.R");
}
