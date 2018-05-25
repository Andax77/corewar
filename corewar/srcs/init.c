/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 18:10:49 by eparisot         ###   ########.fr       */
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

static uint64_t swap_u_int(uint64_t c)
{
	c = ((c << 8) & 0xFF00FF00) | ((c >> 8) & 0xFF00FF);
	return ((c << 16) | ((c >> 16) & 0xFFFF));
}

static void		populate_instru(t_list **instru, uint64_t c)
{
	char		*tmp;
	t_list		*new;

	tmp = ft_itoa(swap_u_int(c));
	if (!*(instru))
		*instru = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	else
	{
		new = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		ft_lstaddend(instru, new);
	}
	free(tmp);
}

static int		get_champ(t_cor *cor)
{
	uint64_t	c;
	int			fd;

	if (cor->champs->path)
	{
		fd = open(cor->champs->path, O_RDONLY);
		while (read(fd, &c, 8))
			populate_instru(&(cor->champs->instru), c);
		close(fd);
		// TO be destroyed
		cor->champs->name = malloc(sizeof(char));
		cor->champs->comment = malloc(sizeof(char));
		//
	}
	return (SUCCESS);
}

static int	init_cor(t_cor *cor, char **argv)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	cor->champs = (t_champ*)ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	while (*argv)
	{
		if (ft_strstr(*argv, ".cor") && ++n && n <= MAX_PLAYERS)
			cor->champs->path = ft_strdup(*argv);
		if (!get_champ(cor))
			return (ERROR);
		argv++;
	}
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
