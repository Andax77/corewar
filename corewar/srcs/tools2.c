/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/19 20:39:51 by eparisot         ###   ########.fr       */
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

void	legacy(t_cor *cor, t_champ *champ, int id, int pc)
{
	t_list		*tmp;
	t_champ		child;
	t_list		*new;
	int			i;

	i = 0;
	ft_printf("debut\n");
	tmp = cor->champs;
	while (tmp)
	{
		i++;
	ft_printf("%d\n", i);
		if (((t_champ*)tmp->content)->id == id && tmp->next && ((t_champ*)tmp->next->content)->id != id)
			break ;
		tmp = tmp->next;
	}
	ft_printf("end\n");
	ft_bzero(&child, sizeof(t_champ));
	ft_memcpy(&child, champ, sizeof(t_champ));//TODO malloc each value
	child.father = id;
	ft_printf("child %d\n", child.id);
	new = ft_lstnew(&child, sizeof(t_champ));
	ft_lstinsert(&cor->champs, new, i);
	ft_printf("end2\n");
}
