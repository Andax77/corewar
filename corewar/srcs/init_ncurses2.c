/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/29 12:31:52 by eparisot         ###   ########.fr       */
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

void		draw_names(t_list *champs)
{
	int		i;
	t_champ	*champ;

	i = 0;
	while (champs)
	{
		champ = champs->content;
		if (!champ->father)
		{
			attron(COLOR_PAIR(i + 3));
			draw_line(11 + (4 * i), 10 + ft_countdigits(champ->v_id), \
				((t_champ*)champs->content)->name);
			i++;
		}
		champs = champs->next;
	}
}

void	init_cmap(t_cor *cor)
{
	int		i;
	t_list	*champs;
	int		nb;
	int		id;

	i = -1;
	id = 0;
	champs = cor->champs;
	nb = ft_lstcount(champs);
	cor->c_map = (short*)ft_malloc(MEM_SIZE * sizeof(short), EXIT_FAILURE);
	while (++i < MEM_SIZE)
		if (champs && i >= id * (MEM_SIZE / nb) && i < (id * (MEM_SIZE / nb)) +\
				(int)((t_champ *)champs->content)->op_nb)
			cor->c_map[i] = 3 + id;
		else
		{
			if (champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			cor->c_map[i] = 2;
		}
}
