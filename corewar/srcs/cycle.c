/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/29 18:35:57 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	processes(t_cor *cor, t_list *champs)
{
	t_champ	*cur_champ;

	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy > -1)
		{
			if (cur_champ->r_cy == 0)
				cycle_job(cor, cur_champ);
			else
				cur_champ->r_cy--;
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
	t_list		*champs;
	int			timeout;
	int			ch;

	ch = ' ';
	timeout = 950;
	while ((champs = cor->champs))
	{
		clean(cor, champs);
		(cor->cycle_to_die && cor->v_cycle == cor->cycle_to_die) ? \
			ret = check_lives(cor) : 0;
		processes(cor, champs);
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
