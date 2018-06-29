/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/29 12:14:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <corewar.h>

static void	init_child(t_champ *child, t_champ *father, t_cor *cor, int pc)
{
	child->id = father->id;
	child->v_id = father->v_id;
	child->pc = pc;
	child->last_pc = pc;
	child->carry = father->carry;
	child->r_cy = change_r_cy(cor, child) - 1;
	child->lives = father->lives;
	child->v_lives = father->v_lives;
}

static int	child_pos(t_cor *cor, int id)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = cor->champs;
	while (tmp)
	{
		i++;
		if (((t_champ*)tmp->content)->id == id)
			break ;
		tmp = tmp->next;
	}
	return (i);
}

void		legacy(t_cor *cor, t_champ *champ, int id, int pc)
{
	t_champ		*child;
	t_list		*new;
	int			i;
	int			j;

	i = child_pos(cor, id);;
	j = -1;
	child = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	ft_bzero(child, sizeof(t_champ));
	if (!((child->reg = ft_memalloc(REG_NUMBER * REG_SIZE))))
		exit(EXIT_FAILURE);
	while (++j < REG_NUMBER)
		child->reg[j] = champ->reg[j];
	init_child(child, champ, cor, pc);
	child->father = id;
	if (!(new = ft_lstnew(child, sizeof(t_champ))))
		exit(EXIT_FAILURE);
	ft_lstinsert(&cor->champs, new, i);
	free(child);
}
