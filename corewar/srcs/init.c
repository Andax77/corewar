/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/31 19:51:56 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	draw_borders(void)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	init_pair(1, COLOR_CYAN, COLOR_CYAN);
	attron(COLOR_PAIR(1));
	while (y < 68)
	{
		if (y == 0 || y == 67 || x == 0 || x == 196 || x == 253)
			mvprintw(y, x, "*");
		x++;
		if (x > 253 && !(x = 0))
			y++;
	}
}

static void	draw_map(t_opt *opt)
{
	int		x;
	int		y;
	char	c[3];

	x = 3;
	y = 2;
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	ft_strcpy(c, (opt->ns) ? "ff\0" : "00\0");
	while (y < 66)
	{
		mvprintw(y, x, c);
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
}

void	draw_char(int pos, unsigned char val, int col_f, int col_b)
{
	int		x;
	int		y;
	char	*c;
	int		i;
	char	*tmp_c;

	x = 3;
	y = 2;
	i = 0;
	init_pair(3, col_f, col_b);
	attron(COLOR_PAIR(3));
	c = ft_itoa_base(val, 16);
	if (ft_strlen(c) < 2)
	{
		tmp_c = c;
		c = ft_strjoin("0", c);
		free(tmp_c);
	}
	while (y < 66)
	{
		if (i == pos)
			mvprintw(y, x, c);
		x = x + 3;
		i++;
		if (x >= 194 && (x = 3))
			y++;
	}
	free(c);
}

int		init_ncurses(t_cor *cor)
{
	if (initscr())
	{
		start_color();
		init_color(COLOR_CYAN, 500, 500, 500);
		draw_borders();
		draw_map(cor->opt);
		//	TEST PRINT CHAMP
		t_champ *champ = cor->champs->content;
		int i = 0;
		while (i < champ->op_nb)
		{
			draw_char(i, champ->splited_prog[i], 2, 0);
			i++;
		}
		// END TEST
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
