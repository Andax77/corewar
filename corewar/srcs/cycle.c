/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/16 13:50:37 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	cycle(t_cor *cor)
{
	t_list		*champs;
	t_list		*first_champ;
	t_champ		*cur_champ;
	int			*last_pc;
	int			*last_champ;
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);
	char		*cycle;
	int			ch;

	last_pc = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	last_champ = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	champs = cor->champs;
	first_champ = champs;
	init_op(f);
	while ((champs = first_champ))
	{
		if (cor->opt->n)
		{
			while (champs)
			{
				//Clean process pos
				cur_champ = champs->content;
				if (last_champ[cur_champ->id - 1] && cur_champ->r_cy == 0)
				{
					attron(COLOR_PAIR(2 + last_champ[cur_champ->id - 1]));
					draw_uchar(last_pc[cur_champ->id - 1], \
							(cor->map)[last_pc[cur_champ->id - 1]]);
				}
				champs = champs->next;
			}
			champs = first_champ;
		}
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				if (cur_champ->r_cy == 0)
				{
					if (cor->cycle != 0)
					{
						// Do op
						if (cor->map[cur_champ->pc] > 1 || cor->map[cur_champ->pc] <= 16)
							f[cor->map[cur_champ->pc]](cor, cur_champ);
						else
							f[0](cor, cur_champ);
					}
					// Change r_cy
					if (cor->map[cur_champ->pc] > 1 || cor->map[cur_champ->pc] <= 16)
						cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
					//Print process pos
					if (cor->opt->n)
					{
						attron(COLOR_PAIR(10 + cur_champ->id));
						draw_uchar(cur_champ->pc, (cor->map)[cur_champ->pc]);
						last_pc[cur_champ->id - 1] = cur_champ->pc;
						last_champ[cur_champ->id - 1] = cur_champ->id;
					}
				}
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		//Print cycle
		cycle = ft_itoa((cor->cycle)++);
		if (cor->opt->n)
		{
			attron(COLOR_PAIR(7));
			draw_line(7, 9, cycle);
		}
		free(cycle);
		//Wait event
		if (cor->opt->n)
		{
			if (ch != ' ')
			{
				noecho();
				ch = getch();
				while (ch != 's' && ch != ' ')
					ch = getch();
				echo();
			}
			else
			{
				usleep(500);
				refresh();
			}
		}
	}
	free(last_pc);
	free(last_champ);
}
