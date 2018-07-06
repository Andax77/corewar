/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/06 16:09:58 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		clean_list(t_list *champs)
{
	t_list	*tmp;

	while (champs->next && ((t_champ*)champs->next->content)->r_cy == -1 && \
			((t_champ*)champs->next->content)->father)
	{
		tmp = champs->next->next;
		ft_lstdelone(&champs->next, del_champ);
		champs->next = tmp;
	}
}

static void	set_cur_op(t_cor *cor, void(**f)(t_cor*, t_champ*))
{
	t_champ	*cur_champ;
	t_list	*champs;

	champs = cor->champs;
	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy > -1)
		{
			if (cur_champ->r_cy == 0)
			{
				cur_champ->cur_op = cor->map[cur_champ->pc];
				cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
			}
			else if ((cur_champ->cur_op != cor->map[cur_champ->pc] && \
			cur_champ->r_cy == g_op_tab[cur_champ->cur_op - 1].nb_cycles - 1))
			{
				if (cor->map[cur_champ->pc] < 1 || cor->map[cur_champ->pc] > 16)
					f[0](cor, cur_champ);
				cur_champ->cur_op = cor->map[cur_champ->pc];
				cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
			}
			else
				cur_champ->r_cy--;
		}
		champs = champs->next;
	}
}

static void	exec_processes(t_cor *cor, t_list *champs, void (**f)(t_cor*,
			t_champ*))
{
	t_champ	*cur_champ;

	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy > -1)
			cycle_job(cor, cur_champ, f);
		else if (cur_champ->r_cy < -1)
		{
			if (cor->opt->v && !cor->opt->d)
			{
				attron(COLOR_PAIR(cur_champ->id + 20));
				draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
			}
		}
		champs = champs->next;
	}
	set_cur_op(cor, f);
}

static int	dump_handler(t_cor *cor)
{
	if (cor->opt->d && cor->opt->d == cor->cycle)
	{
		if (!cor->opt->v)
		{
			dump(cor);
			return (0);
		}
		else
		{
			if (!init_ncurses(cor))
				return (0);
			cor->opt->d = 0;
			jump(cor);
		}
	}
	return (1);
}

void		cycle(t_cor *cor, int ret)
{
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);
	t_list		*champs;
	int			timeout;
	int			ch;

	ch = ' ';
	timeout = 950;
	init_op(f);
	while ((champs = cor->champs))
	{
		(cor->opt->v || cor->opt->d) ? clean(cor, champs) : 0;
		exec_processes(cor, champs, f);
		if (cor->cycle_to_die && cor->v_cycle == cor->cycle_to_die)
			ret = check_lives(cor);
		if (!(dump_handler(cor)))
			break ;
		(cor->opt->v && !cor->opt->d) ? print_infos(cor) : 0;
		(cor->opt->v && !cor->opt->d) ? key_event(&timeout, &ch) : 0;
		if (!ret)
			break ;
		else
		{
			cor->cycle++;
			cor->v_cycle++;
		}
	}
}
