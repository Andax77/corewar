/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/25 00:17:25 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <corewar.h>

void	order_to_start(t_list **champs)
{
	t_list	*cur;
	t_list	*next;

	cur = *champs;
	*champs = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = *champs;
		*champs = cur;
		cur = next;
	}
}

void	legacy(t_cor *cor, t_champ *champ, int id, int pc)
{
	t_list		*tmp;
	t_champ		child;
	t_list		*new;
	int			i;
	int			j;

	i = -1;
	j = -1;
	tmp = cor->champs;
	while (tmp)
	{
		++i;
		if (((t_champ*)tmp->content)->id == id)
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
	child.carry = champ->carry;
	child.r_cy = change_r_cy(cor, &child);
	child.father = id;
	new = ft_lstnew(&child, sizeof(t_champ));
	ft_lstinsert(&cor->champs, new, i);
}
