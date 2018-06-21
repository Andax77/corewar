/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/20 01:55:44 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_winner(t_cor *cor)
{
	t_list	*champ;
	t_champ	*tmp;
	t_champ	*winner;
	int		first;

	first = 0;
	champ = cor->champs;
	ft_printf("Introducing contestants...\n");
	while (champ)
	{
		if (first == 0 && ++first && champ->next &&\
			(tmp = (t_champ*)champ->content))
			champ = champ->next;
		if (((t_champ*)champ->content)->v_id == cor->winner && \
			((t_champ*)champ->content)->father == 0)
			winner = (t_champ*)champ->content;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",\
		((t_champ*)champ->content)->v_id, ((t_champ*)champ->content)->op_nb,\
		((t_champ*)champ->content)->name, ((t_champ*)champ->content)->comment);
		champ = champ->next;
	}
	if (tmp)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",\
		tmp->v_id, tmp->op_nb, tmp->name, tmp->comment);
	ft_printf("Contestant %d, \"%s\", has won !\n", cor->winner, winner->name);
}
