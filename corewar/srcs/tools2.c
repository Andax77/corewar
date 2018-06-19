/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/19 15:19:24 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <corewar.h>

void	order_to_start(t_list **champs)
{
	t_list	*last_champ;
	t_list	*cur_champ;
	t_list	*first_champ;

	first_champ = *champs;
	cur_champ = *champs;
	while (cur_champ->next->next)
		cur_champ = cur_champ->next;
	last_champ = cur_champ->next;
	cur_champ->next = NULL;
	last_champ->next = first_champ;
	*champs = last_champ;
}
