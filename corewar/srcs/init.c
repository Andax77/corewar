/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/04 21:01:21 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	draw_borders(void)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < 68)
	{
		if (y == 0 || y == 67 || x == 0 || x == 196 || x == 253)
			mvprintw(y, x, "*");
		x++;
		if (x > 253 && !(x = 0))
			y++;
	}
}

static void	draw_map(t_cor *cor)
{
	int		i;
	t_list	*champs;
	int		nb;
	int		id;

	i = -1;
	id = 0;
	champs = cor->champs;
	nb = ft_lstcount(champs);
	while (++i < MEM_SIZE)
		if (champs && i >= id * (MEM_SIZE / nb) && i < (id * (MEM_SIZE / nb)) +\
				(int)((t_champ *)champs->content)->op_nb)
		{
			init_pair(3 + id, COLOR_RED + id, COLOR_BLACK);
			attron(COLOR_PAIR(3 + id));
			(cor->opt->ns) ? draw_uchar(i, 0xff) : draw_uchar(i, cor->map[i]);
		}
		else
		{
			attron(COLOR_PAIR(2));
			if (champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			(cor->opt->ns) ? draw_uchar(i, 0xff) : draw_uchar(i, cor->map[i]);
		}
}

void		draw_line(int line_idx, char *line)
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

void		draw_uchar(int pos, unsigned char val)
{
	int		x;
	int		y;
	char	*c;
	int		i;
	char	*tmp_c;

	x = 3;
	y = 2;
	i = 0;
	c = ft_itoa_base(val, 16);
	if (ft_strlen(c) < 2)
	{
		tmp_c = c;
		c = ft_strjoin("0", c);
		free(tmp_c);
	}
	while (y < 66)
	{
		if (i++ == pos)
			mvprintw(y, x, c);
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
	free(c);
}

static void	draw_infos(int nb)
{
	draw_line(2, "** PAUSED **");
	draw_line(4, "Cycles/second limit :");
	draw_line(7, "Cycle :");
	draw_line(9, "Processes :");
	draw_line(11, "Player 1 :");
	draw_line(12, "  Last live :			");
	draw_line(13, "  Lives in current period :	");
	(nb > 1) ? draw_line(15, "Player 2 :") : 0;
	(nb > 1) ? draw_line(16, "  Last live :			") : 0;
	(nb > 1) ? draw_line(17, "  Lives in current period :	") : 0;
	(nb > 2) ? draw_line(19, "Player 3 :") : 0;
	(nb > 2) ? draw_line(20, "  Last live :			") : 0;
	(nb > 2) ? draw_line(21, "  Lives in current period :	") : 0;
	(nb > 3) ? draw_line(23, "Player 4 :") : 0;
	(nb > 3) ? draw_line(24, "  Last live :			") : 0;
	(nb > 3) ? draw_line(25, "  Lives in current period :	") : 0;
	nb = 4 * (nb - 1);
	draw_line(15 + nb, "Live breakdown for current period :");
	draw_line(16 + nb, "[--------------------------------------------------]");
	draw_line(18 + nb, "Live breakdown for last period :");
	draw_line(19 + nb, "[--------------------------------------------------]");
	draw_line(21 + nb, "CYCLES_TO_DIE :");
	draw_line(23 + nb, "CYCLE_DELTA :");
	draw_line(25 + nb, "NBR_LIVE :");
	draw_line(27 + nb, "MAX_CHECKS :");
}

void		draw_cow(int nb)
{
	nb = 27 + (4 * (nb - 1));
	draw_line(nb++, "----------------------------------------------------");
	draw_line(nb++, "");
	draw_line(nb++, "");
	draw_line(nb++, "");
	draw_line(nb++, "");
	draw_line(nb++, "		    __    ____");
	draw_line(nb++, "		   /{_\\_/   `'\\____");
	draw_line(nb++, "		    \\___  (o)  (o   }");
	draw_line(nb++, "		     /            -'ô");
	draw_line(nb++, "		     #   \\_    `__\\");
	draw_line(nb++, "		    ###   \\__ (o'o)");
	draw_line(nb++, "		   ###    #(  `===='");
	draw_line(nb++, "		  ####     ##|                           __");
	draw_line(nb++, "		 ##         ###|                        //");
	draw_line(nb++, "		 #            #)                       //");
	draw_line(nb++, "		 |   ###    \\###|_____    //nnnnnnn/--//");
	draw_line(nb++, "		 |    ###    \\________|\\ //nnnnnnn/  //");
	draw_line(nb++, "		 |#    ##           | | //nnnnnnn/  //");
	draw_line(nb++, "		 |##       \\--------°- //nnnnnnn/  //");
	draw_line(nb++, "		 |###       ####|     //nnnnnnn/  //");
	draw_line(nb++, "                              ------------");
	draw_line(nb++, "");
	draw_line(nb++, "");
	draw_line(nb++, "");
	draw_line(nb++, "			 C.O.W -- W.A.R");
}

int			init_ncurses(t_cor *cor)
{
	if (initscr())
	{
		start_color();
		init_color(COLOR_MAGENTA, 500, 500, 500);
		init_color(COLOR_WHITE, 1000, 1000, 1000);
		init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		draw_borders();
		attron(COLOR_PAIR(2));
		draw_map(cor);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
		attron(COLOR_PAIR(7));
		draw_infos(ft_lstcount(cor->champs));
		draw_cow(ft_lstcount(cor->champs));
		curs_set(0);
		return (1);
	}
	return (0);
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
