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
	int		first;

	tmp = NULL;
	if ((champ = cor->champs) && ft_printf("Introducing contestants...\n"))
		first = 0;
	while (champ)
	{
		if (first == 0 && ++first && champ->next &&\
			(tmp = (t_champ*)champ->content))
			champ = champ->next;
		if (((t_champ*)champ->content)->father == 0)
			ft_printf("{%s}* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\
			\n{eoc}", color_player(((t_champ*)champ->content)->id),\
		((t_champ*)champ->content)->v_id, ((t_champ*)champ->content)->op_nb,\
		((t_champ*)champ->content)->name, ((t_champ*)champ->content)->comment);
		champ = champ->next;
	}
	if (tmp)
		ft_printf("{%s}* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n{eoc}",
	color_player(tmp->id), tmp->v_id, tmp->op_nb, tmp->name, tmp->comment);
}

char		*color_player(int id)
{
	if (id == 1)
		return ("red");
	else if (id == 2)
		return ("green");
	else if (id == 3)
		return ("yellow");
	else if (id == 4)
		return ("blue");
	return ("eoc");
}

char		*get_name_champ(t_cor *cor)
{
	t_list	*champ;
	t_champ	*winner;

	champ = cor->champs;
	while (champ)
	{
		if (((t_champ*)champ->content)->v_id == cor->winner && \
			((t_champ*)champ->content)->father == 0)
			winner = (t_champ*)champ->content;
		champ = champ->next;
	}
	return (winner->name);
}
