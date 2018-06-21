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
	t_list *champ;

	champ = cor->champs;
	ft_printf("Introducing contestants...\n");

	while (champ)
	{
		ft_printf("* Player %d, \"%s\" !\n", ((t_champ *)champ->content)->v_id,\
		((t_champ *)champ->content)->name);
		champ = champ->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", cor->winner, "andrew");
}
