/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/02 20:49:59 by eparisot         ###   ########.fr       */
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
	int		id;
	t_champ	*champ;

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

int		get_v_ids(t_list *champs, int id, int *nb)
{
	char	*tmp;
	t_list	*champ;

	champ = champs;
	while (champ)
	{
		if (((t_champ*)champ->content)->father == 0 && \
				((t_champ*)champ->content)->id == id)
		{
			draw_line(*nb, 0, "Player");
			tmp = ft_itoa(((t_champ*)champ->content)->v_id);
			draw_line(*nb, 7, tmp);
			draw_line(*nb, 7 + ft_strlen(tmp) + 1, ":");
			free(tmp);
			draw_line(++*nb, 0, "  Last live :");
			draw_line(++*nb, 0, "  Lives in current period :");
			*nb += 2;
			id++;
			break ;
		}
		champ = champ->next;
	}
	return (id);
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
			if (champs && champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			cor->c_map[i] = 2;
		}
}
