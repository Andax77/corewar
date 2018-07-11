/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:05:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/11 21:03:54 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	ft_live_bis(t_cor *cor, t_champ *champ)
{
	champ->last_live = cor->cycle;
	champ->lives++;
	cor->winner = champ->id;
}

static void	ft_live_for_other(t_cor *cor, t_list *tmp, int p, t_champ *champ)
{
	while (tmp)
	{
		if (((t_champ*)tmp->content)->v_id == p
				&& ((t_champ*)tmp->content)->father == 0
				&& (t_champ*)tmp->content != champ)
		{
			((t_champ*)tmp->content)->lives++;
			cor->winner = ((t_champ*)tmp->content)->id;
			((t_champ*)tmp->content)->last_live = cor->cycle;
			get_color_heart(1, "Faire un live", ((t_champ*)tmp->content)->id);
			break ;
		}
		tmp = tmp->next;
	}
}

void		ft_live(t_cor *cor, t_champ *champ)
{
	int		p;
	t_list	*tmp;

	tmp = cor->champs;
	p = (cor->map[++champ->pc % MEM_SIZE] << 24)
		+ (cor->map[++champ->pc % MEM_SIZE] << 16)
		+ (cor->map[++champ->pc % MEM_SIZE] << 8)
		+ cor->map[++champ->pc % MEM_SIZE];
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	champ->v_lives++;
	champ->x_lives++;
	(p == champ->v_id) ? ft_live_bis(cor, champ) : 0;
	ft_live_for_other(cor, tmp, p, champ);
}
