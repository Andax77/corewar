/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/01 12:29:31 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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
	char	*str;
	char	*tmp;
	int		x;
	int		y;
	int		i;

	x = 3;
	y = 2;
	i = 0;
	if (!(str = ft_itoa_base(val, 16)))
		exit(EXIT_FAILURE);
	if (ft_strlen(str) < 2)
	{
		tmp = str;
		if (!(str = ft_strjoin("0", tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
	}
	while (y < 66)
	{
		if (i++ == pos % MEM_SIZE)
			mvprintw(y, x, str);
		x = x + 3;
		if (x >= 194 && (x = 3))
			y++;
	}
	free(str);
}

void		draw_names(t_list *champs)
{
	t_champ	*champ;
	int		id;

	while (champs)
	{
		champ = champs->content;
		if (!champ->father)
		{
			id = champ->id;
			attron(COLOR_PAIR(id + 2));
			draw_line(11 + (4 * (id - 1)), 10 + ft_countdigits(champ->v_id), \
				((t_champ*)champs->content)->name);
		}
		champs = champs->next;
	}
}

void	init_cmap(t_cor *cor)
{
	t_list	*champs;
	int		i;
	int		nb;
	int		id;

	i = -1;
	id = 0;
	champs = cor->champs;
	nb = ft_lstcount(champs);
	cor->c_map = (short*)ft_malloc(MEM_SIZE * sizeof(short), EXIT_FAILURE);
	while (++i < MEM_SIZE)
		if (champs && i >= id * (MEM_SIZE / nb) && \
i < (id * (MEM_SIZE / nb)) + (int)((t_champ *)champs->content)->op_nb)
			cor->c_map[i] = 3 + id;
		else
		{
			if (champs && champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			cor->c_map[i] = 2;
		}
}
