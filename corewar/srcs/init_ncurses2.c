/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/12 18:31:19 by eparisot         ###   ########.fr       */
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
		(i++ == pos % MEM_SIZE) ? mvprintw(y, x, str) : 0;
		x = x + 3;
		(x >= 194 && (x = 3)) ? y++ : 0;
	}
	free(str);
}

void		draw_names(t_list *champs)
{
	t_champ	*champ;
	int		id;
	char	*name;

	while (champs)
	{
		champ = champs->content;
		if (!champ->father)
		{
			id = champ->id;
			name = ft_strndup(((t_champ*)champs->content)->name, 42);
			attron(COLOR_PAIR(id + 2));
			draw_line(11 + (4 * (id - 1)), 10 + ft_countdigits(champ->v_id),
					name);
			ft_fruit(1, &name);
		}
		champs = champs->next;
	}
}

int			get_v_ids(t_list *champs, int id, int *nb)
{
	char	*tmp;
	t_list	*champ;

	champ = champs;
	while (champ)
	{
		if (((t_champ*)champ->content)->father == 0
				&& ((t_champ*)champ->content)->id == id)
		{
			draw_line(*nb, 0, "Player");
			if (!(tmp = ft_itoa(((t_champ*)champ->content)->v_id)))
				exit(EXIT_FAILURE);
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

void		init_cmap(t_cor *cor)
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
		if (champs && i >= id * (MEM_SIZE / nb) && i < (id * (MEM_SIZE / nb))
				+ (int)((t_champ *)champs->content)->op_nb)
			cor->c_map[i] = 3 + id;
		else
		{
			if (champs && champs->next && i == (id + 1) * (MEM_SIZE / nb) - 1)
				if (++id < MAX_PLAYERS)
					champs = champs->next;
			cor->c_map[i] = 2;
		}
}
