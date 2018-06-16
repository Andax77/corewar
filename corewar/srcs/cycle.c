/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/16 18:39:00 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	clean(t_cor *cor, t_list *champs, int *last_champ, int *last_pc)
{
	t_champ *cur_champ;

	while (champs)
	{
		cur_champ = champs->content;
		if (last_champ[cur_champ->id - 1] && cur_champ->r_cy == 0)
		{
			attron(COLOR_PAIR(2 + last_champ[cur_champ->id - 1]));
			draw_uchar(last_pc[cur_champ->id - 1], \
					(cor->map)[last_pc[cur_champ->id - 1]]);
		}
		champs = champs->next;
	}
}

void	cycle_job(t_cor *cor, t_champ *cur_champ, int *last_champ, int *last_pc)
{
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);

	init_op(f);
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
	// Print process pos
	if (cor->opt->n)
	{
		attron(COLOR_PAIR(10 + cur_champ->id));
		draw_uchar(cur_champ->pc, (cor->map)[cur_champ->pc]);
		last_pc[cur_champ->id - 1] = cur_champ->pc;
		last_champ[cur_champ->id - 1] = cur_champ->id;
	}
}

void	cycle(t_cor *cor)
{
	t_list		*champs;
	t_list		*first_champ;
	t_champ		*cur_champ;
	int			*last_pc;
	int			*last_champ;
	char		*cycle;
	int			ch;
	int			timeout;
	char		*p_p_c;

	timeout = 950;
	last_pc = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	last_champ = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	champs = cor->champs;
	first_champ = champs;
	while ((champs = first_champ))
	{
		// Clean cursor
		if (cor->opt->n)
			clean(cor, champs, last_champ, last_pc);
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				if (cur_champ->r_cy == 0)
					cycle_job(cor, cur_champ, last_champ, last_pc);
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		// Print infos
		cycle = ft_itoa((cor->cycle)++);
		p_p_c = ft_itoa(1000 - timeout);
		if (cor->opt->n)
		{
			attron(COLOR_PAIR(7));
			draw_line(7, 9, cycle);
			attron(COLOR_PAIR(7));
			draw_line(4, 22, p_p_c);
		}
		free(p_p_c);
		free(cycle);
		// Key event
		if (cor->opt->n)
		{
			if (ch != ' ')
			{
				noecho();
				ch = getch();
				while (ch != 's' && ch != ' ')
				{
					if (ch == 'e' && timeout > 1)
					{
						p_p_c = ft_itoa(1000 - --timeout);
						attron(COLOR_PAIR(7));
						draw_line(4, 22, "    ");
						draw_line(4, 22, p_p_c);
						free(p_p_c);
					}
					else if (ch == 'r' && timeout > 1)
					{
						if (1000 - (timeout - 10) > 1000)
							p_p_c = ft_itoa(1000 - (timeout = 0));
						else
							p_p_c = ft_itoa(1000 - (timeout -= 10));
						attron(COLOR_PAIR(7));
						draw_line(4, 22, "    ");
						draw_line(4, 22, p_p_c);
						free(p_p_c);
					}
					else if (ch == 'w' && timeout < 950)
					{
						p_p_c = ft_itoa(1000 - ++timeout);
						attron(COLOR_PAIR(7));
						draw_line(4, 22, "    ");
						draw_line(4, 22, p_p_c);
						free(p_p_c);
					}
					else if (ch == 'q' && timeout < 950)
					{
						if (1000 - (timeout + 10) < 50)
							p_p_c = ft_itoa(1000 - (timeout = 950));
						else
							p_p_c = ft_itoa(1000 - (timeout += 10));
						attron(COLOR_PAIR(7));
						draw_line(4, 22, "    ");
						draw_line(4, 22, p_p_c);
						free(p_p_c);
					}
					ch = getch();
				}
				echo();
			}
			else
			{
				usleep(timeout);
				refresh();
			}
		}
	}
	free(last_pc);
	free(last_champ);
}
