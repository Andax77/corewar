/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 16:07:05 by eparisot         ###   ########.fr       */
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

static void	init_ncurse(t_opt *opt)
{
	initscr();
	start_color();
	init_color(COLOR_CYAN, 500, 500, 500);
	draw_borders();
	draw_map(opt);
	curs_set(0);
}



static int	check_champs(char **champs)
{
	int		i;
	int		fd;
	int32_t	c;
	char	*line;

	line = NULL;
	i = 0;
	while (champs[i])
	{
		fd = open(champs[i], O_RDONLY);
		while (read(fd, &c, 8) > 0)
		{
			c = ((c << 8) & 0xFF00FF00) | ((c >> 8) & 0xFF00FF);
			c = ((c << 16) | ((c >> 16) & 0xFFFF));
			ft_printf("readen char = %x\n", c);
		}
		close(fd);
		i++;
	}
	return (SUCCESS);
}

static int	init_cor(t_cor *cor, char **argv)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (argv[i])
		if (ft_strstr(argv[i++], ".cor"))
			n++;
	cor->champs = (char**)ft_malloc((n + 1) * sizeof(char*), EXIT_FAILURE);
	i = 0;
	while (*argv)
	{
		if (ft_strstr(*argv, ".cor"))
			cor->champs[i++] = ft_strdup(*argv);
		argv++;
	}
	cor->champs[i] = NULL;
	if (!check_champs(cor->champs))
		return (ERROR);
	if (!(cor->map = ft_strnew(4096)))
		exit(EXIT_FAILURE);
	//TODO GOGO Algo
	return (SUCCESS);
}

int			init(char **argv, t_cor *cor)
{
	if (cor->opt->n)
		init_ncurse(cor->opt);
	if (init_cor(cor, argv) == ERROR)
		return (ERROR);
	if (cor->opt->n)
	{
		getch();
		endwin();
	}
	return (SUCCESS);
}
