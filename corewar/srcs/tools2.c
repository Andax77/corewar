/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/22 19:15:04 by eparisot         ###   ########.fr       */
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
	int			j;

	i = 0;
	j = -1;
	tmp = cor->champs;
	while (tmp)
	{
		i++;
		if (((t_champ*)tmp->content)->id == id && tmp->next && ((t_champ*)tmp->next->content)->id != id)
			break ;
		tmp = tmp->next;
	}
	ft_bzero(&child, sizeof(t_champ));
	if (!((child.reg = ft_memalloc(REG_NUMBER * REG_SIZE))))
		exit(EXIT_FAILURE);
	while (++j < REG_NUMBER)
		child.reg[j] = champ->reg[j];
	child.id = champ->id;
	child.v_id = champ->v_id;
	child.pc = pc;
	child.last_pc = pc;
//	ft_printf("{magenta}->%d{eoc}\n", pc);/////////////////////////////////////////////print
	child.carry = champ->carry;
	child.r_cy = change_r_cy(cor, &child);
	child.father = id;
	new = ft_lstnew(&child, sizeof(t_champ));
	ft_lstinsert(&cor->champs, new, i);
//	free(child.reg);
//	ft_lstdel(&new, del);
	//
//	tmp = cor->champs;
//	while (tmp)
//	{
//		ft_printf("{red}%d{eoc}\n", ((t_champ*)(tmp->content))->father);
//		tmp = tmp->next;
//	}
//	ft_printf("\n");
}
