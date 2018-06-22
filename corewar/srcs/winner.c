/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/21 18:40:07 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_winner(t_cor *cor)
{
	t_list	*champ;
	t_champ	*tmp;
	t_champ	*winner;
	int		first;

	if ((champ = cor->champs) && ft_printf("Introducing contestants...\n"))// separer cette fonction et appeler le debut au debut du programme
		first = 0;
	while (champ)
	{
		if (((t_champ*)champ->content)->v_id == cor->winner && \
			((t_champ*)champ->content)->father == 0)
			winner = (t_champ*)champ->content;
		if (first == 0 && ++first && champ->next &&\
			(tmp = (t_champ*)champ->content))
			champ = champ->next;
		if (((t_champ*)champ->content)->father == 0)
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
