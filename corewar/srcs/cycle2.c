/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/04 22:25:53 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	clean_print(t_cor *cor, t_champ *cur_champ, int id)
{
	if (cor->opt->v && !cor->opt->d)
	{
		attron(COLOR_PAIR(40 + id));
		draw_uchar(cur_champ->last_pc, \
			cor->map[cur_champ->last_pc]);
		if (cur_champ->last_pc != cur_champ->last_live_pc)
		{
			attron(COLOR_PAIR(cor->c_map[cur_champ->last_live_pc]));
			draw_uchar(cur_champ->last_live_pc, \
				cor->map[cur_champ->last_live_pc]);
		}
	}
	cur_champ->last_live_pc = cur_champ->last_pc;
}

void		clean(t_cor *cor, t_list *champs)
{
	t_champ		*cur_champ;
	int			id;

	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy == 0)
		{
			if ((id = check_live_value(cor, cur_champ->last_pc)))
				clean_print(cor, cur_champ, id);
			else if (cor->opt->v && !cor->opt->d)
			{
				attron(COLOR_PAIR(cor->c_map[cur_champ->last_pc]));
				draw_uchar(cur_champ->last_pc, \
					cor->map[cur_champ->last_pc]);
			}
		}
		champs = champs->next;
	}
}

void		cycle_job(t_cor *cor, t_champ *cur_champ, void (**f)(t_cor*,
																	t_champ*))
{
	if (cor->cycle != 0)
	{
		if (cur_champ->cur_op >= 1 && cur_champ->cur_op <= 16)
			f[cur_champ->cur_op](cor, cur_champ);
		else
			f[0](cor, cur_champ);
	}
	else
		cur_champ->cur_op = cor->map[cur_champ->pc];
	if (cor->opt->v && !cor->opt->d)
	{
		attron(COLOR_PAIR(cur_champ->id + 20));
		draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
	}
	cur_champ->last_pc = cur_champ->pc;
}

static void	check_champs_lives(t_cor* cor, int *nbr_lives, int *nbr_v_lives)
{
	t_list	*champs;

	champs = cor->champs;
	while (champs)
	{
		*nbr_v_lives += ((t_champ*)champs->content)->v_lives;
		*nbr_lives += ((t_champ*)champs->content)->lives;
		if (!((t_champ*)champs->content)->v_lives)
		{
			((t_champ*)champs->content)->r_cy = -1;
			if (cor->opt->v && !cor->opt->d)
			{
				attron(COLOR_PAIR(cor->c_map[((t_champ*)champs->content)->pc]));
				draw_uchar(((t_champ*)champs->content)->pc, \
					cor->map[((t_champ*)champs->content)->pc]);
			}
		}
		((t_champ*)champs->content)->lives = 0;
		((t_champ*)champs->content)->v_lives = 0;
		clean_list(champs);
		champs = champs->next;
	}
}

int			check_lives(t_cor *cor)
{
	int		nbr_lives;
	int		nbr_v_lives;

	nbr_lives = 0;
	nbr_v_lives = 0;
	cor->v_cycle = 0;
	check_champs_lives(cor, &nbr_lives, &nbr_v_lives);
	if (nbr_lives >= NBR_LIVE || cor->checks == MAX_CHECKS - 1)
	{
		cor->cycle_to_die -= CYCLE_DELTA;
		cor->checks = 0;
	}
	else
		cor->checks++;
	if (cor->cycle_to_die <= 0 || nbr_v_lives == 0)
	{
		if (cor->cycle_to_die <= 0)
			cor->cycle_to_die = 0;
		return (0);
	}
	return (1);
}
