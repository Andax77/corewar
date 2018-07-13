/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/13 14:57:23 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	ft_init_child(t_champ *child, t_champ *father, t_cor *cor, int pc)
{
	if (!(child->name = ft_strdup(father->name)))
		exit(EXIT_FAILURE);
	child->id = father->id;
	child->v_id = father->v_id;
	child->pc = pc;
	child->last_pc = pc;
	child->carry = father->carry;
	child->r_cy = change_r_cy(cor, child) - 1;
	child->cur_op = cor->map[child->pc];
	child->last_live = 0;
	child->lives = father->lives;
	child->v_lives = father->v_lives;
}

void		legacy(t_cor *cor, t_champ *champ, int id, int pc)
{
	t_champ		*child;
	t_list		*new;
	int			reg_number;
	int			j;

	reg_number = REG_NUMBER;
	j = -1;
	child = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (!((child->reg = ft_memalloc(reg_number * sizeof(int)))))
		exit(EXIT_FAILURE);
	while (++j < reg_number)
		child->reg[j] = champ->reg[j];
	ft_init_child(child, champ, cor, pc);
	child->father = id;
	if (!(new = ft_lstnew(child, sizeof(t_champ))))
		exit(EXIT_FAILURE);
	ft_lstadd(&cor->champs, new);
	free(child);
}
