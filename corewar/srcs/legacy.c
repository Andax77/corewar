/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/02 18:57:37 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <corewar.h>

static void	init_child(t_champ *child, t_champ *father, t_cor *cor, int pc)
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
	child->lives = father->lives;
	child->v_lives = father->v_lives;
}

void		legacy(t_cor *cor, t_champ *champ, int id, int pc)
{
	t_champ		*child;
	t_list		*new;
	int			j;

	j = -1;
	child = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (!((child->reg = ft_memalloc(REG_NUMBER * sizeof(int)))))
		exit(EXIT_FAILURE);
	while (++j < REG_NUMBER)
		child->reg[j] = champ->reg[j];
	init_child(child, champ, cor, pc);
	child->father = id;
	if (!(new = ft_lstnew(child, sizeof(t_champ))))
		exit(EXIT_FAILURE);
	ft_lstadd(&cor->champs, new);
	free(child);
}
