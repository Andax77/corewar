/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/02 18:29:22 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	exec_processes(t_cor *cor, t_list *champs, void (**f)(t_cor*,
																	t_champ*))
{
	t_champ	*cur_champ;

	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy > -1)
		{
			if (cur_champ->r_cy == 0)
				cycle_job(cor, cur_champ, f);
			else
			{
				cur_champ->r_cy--;
				if (cor->opt->v)
				{
					attron(COLOR_PAIR(cur_champ->id + 20));
					draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
				}
			}
		}
		champs = champs->next;
	}
}

static int	dump_handler(t_cor *cor)
{
	if (cor->opt->d && cor->opt->d == cor->cycle)
	{
		if (!cor->opt->v)
		{
			dump(cor);

t_list	*tmp = cor->champs;
while (tmp)
{
ft_printf("id = %d - %d ; pc = %d\n", ((t_champ*)tmp->content)->id, ((t_champ*)tmp->content)->father, ((t_champ*)tmp->content)->pc);
tmp = tmp->next;
}

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
		if (cor->cycle_to_die && cor->v_cycle == cor->cycle_to_die)
			ret = check_lives(cor);
		exec_processes(cor, champs, f);
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
