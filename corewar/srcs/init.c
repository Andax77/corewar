/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/18 18:55:28 by eparisot         ###   ########.fr       */
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
			draw_uchar(i, cor->map[i]);
		}
		else
		{
			attron(COLOR_PAIR(2));
			if (champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			draw_uchar(i, cor->map[i]);
		}
}

void		draw_line(int line_idx, int col_idx, char *line)
{
	int		x;
	int		y;

	x = 199 + col_idx;
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
		if (i++ == pos % MEM_SIZE)
			mvprintw(y, x, c);
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
	free(c);
}

static void	draw_infos(t_list *champs)
{
	char	*tmp;
	int		nb;

	nb = 11;
	draw_line(2, 0, "** PAUSED **");
	draw_line(4, 0, "Cycles/second limit :");
	draw_line(7, 0, "Cycle :");
	draw_line(9, 0, "Processes :");
	while (champs)
	{
		draw_line(nb, 0, "Player");
		tmp = ft_itoa(((t_champ*)champs->content)->v_id);
		draw_line(nb, 7, tmp);
		draw_line(nb, 7 + ft_strlen(tmp) + 1, ":");
		free(tmp);
		draw_line(++nb, 0, "  Last live :			");
		draw_line(++nb, 0, "  Lives in current period :	");
		nb += 2;
		champs = champs->next;
	}
	draw_line(27, 0, "CYCLES_TO_DIE :");
	draw_line(29, 0, "CYCLE_DELTA :");
	draw_line(31, 0, "NBR_LIVE :");
	draw_line(33, 0, "MAX_CHECKS :");
}

void		draw_names(t_list *champs)
{
	int		i;
	t_champ	*champ;

	i = 0;
	while (champs)
	{
		champ = champs->content;
		attron(COLOR_PAIR(i + 3));
		draw_line(11 + (4 * i), 10 + ft_countdigits(champ->v_id), \
				((t_champ*)champs->content)->name);
		i++;
		champs = champs->next;
	}
}

static void	init_colors(t_list *champs)
{
	t_list	*tmp;
	int		i;

	tmp = champs;
	while (champs)
	{
		i = ((t_champ*)champs->content)->id;
		init_pair(i + 20, COLOR_BLACK, i);
		champs = champs->next;
	}
	champs = tmp;
	while (champs)
	{
		i = ((t_champ*)champs->content)->id;
		init_pair(i + 40, COLOR_WHITE, i);
		champs = champs->next;
	}
}

int			init_ncurses(t_cor *cor)
{
	if (initscr())
	{
		start_color();
		init_color(COLOR_MAGENTA, 500, 500, 500);
		init_color(17, 1000, 1000, 1000);
		init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		draw_borders();
		attron(COLOR_PAIR(2));
		draw_map(cor);
		init_pair(17, 17, COLOR_BLACK);
    attron(COLOR_PAIR(17));
		draw_infos(cor->champs);
		init_colors(cor->champs);
		draw_names(cor->champs);
		curs_set(0);
		print_player(4, ft_lstcount(cor->champs));
		return (1);
	}
	return (0);
}

int			init(char **argv, t_cor *cor)
{
	if (init_cor(cor, argv) == ERROR)
		return (ERROR);
	if (cor->opt->v)
	{
		getch();
		endwin();
	}
	return (SUCCESS);
}
