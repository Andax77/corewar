/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:05:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/05 01:34:57 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_live(t_cor *cor, t_champ *champ)
{
	int		p;
	t_list	*tmp;

	tmp = cor->champs;
	p = (cor->map[++champ->pc % MEM_SIZE] << 24) + \
	(cor->map[++champ->pc % MEM_SIZE] << 16) + \
	(cor->map[++champ->pc % MEM_SIZE] << 8) + \
	cor->map[++champ->pc % MEM_SIZE];
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	// count lives for process
	champ->v_lives++;
	if (p == champ->v_id)
	{
		// record last live cycle
		champ->last_live = cor->cycle;
		champ->lives++;
		cor->winner = champ->id;
	}
	// check if live for another process (father or not)
	while (tmp)
	{
		if (((t_champ*)tmp->content)->v_id == p && \
	((t_champ*)tmp->content)->father == 0 && (t_champ*)tmp->content != champ)
		{
			((t_champ*)tmp->content)->lives++;
			//((t_champ*)tmp->content)->v_lives++;
			cor->winner = ((t_champ*)tmp->content)->id;
			((t_champ*)tmp->content)->last_live = cor->cycle;
			get_color_heart(1, "Faire un live", ((t_champ*)tmp->content)->id);
			break ;
		}
		tmp = tmp->next;
	}
}
