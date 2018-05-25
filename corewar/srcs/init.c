/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 20:38:11 by eparisot         ###   ########.fr       */
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

static void		populate_instru(t_champ **champ, uint64_t c)
{
	t_list		**instru;
	char		*tmp;
	t_list		*new;

	instru = &(*champ)->instru;
	if (!(tmp = ft_itoa(swap_u_int(c))))
		exit(EXIT_FAILURE);
	if (*instru == NULL)
	{
		if (!(*instru = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
		ft_lstaddend(instru, new);
	}
	free(tmp);
}

static int		get_champ(t_champ **champ, char *path)
{
	uint64_t	c;
	int			fd;

	if (path)
	{
		fd = open(path, O_RDONLY);
		while (read(fd, &c, 8))
			populate_instru(champ, c);
		close(fd);
	}
	return (SUCCESS);
}

static int		populate_champs(t_list **champs, char *path)
{
	t_list		*new;
	t_champ		*champ;

	champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (!get_champ(&champ, path))
		return (ERROR);
	if (!*(champs))
	{
		if (!(*champs = ft_lstnew(champ, sizeof(t_champ))))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(champ, sizeof(t_champ))))
			exit(EXIT_FAILURE);
		ft_lstaddend(champs, new);
	}
	free(champ);
	return (SUCCESS);
}

static int	init_cor(t_cor *cor, char **argv)
{
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (*argv)
	{
		if (ft_strstr(*argv, ".cor") && ++n && n <= MAX_PLAYERS)
			populate_champs(&cor->champs, *argv);
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
