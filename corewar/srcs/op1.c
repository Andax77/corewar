/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:05:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/17 19:49:06 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_live(t_cor *cor, t_champ *champ)
{
	int		p;

	champ->last_live_pc = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 24) + (cor->map[++champ->pc % MEM_SIZE] << 16) +
		(cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	champ->lives++;
	champ->last_live = cor->cycle;
}

void	ft_ld(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 2) % IDX_MOD;
	p2 = recup_content(cor, champ, ocp, 4, 2);
	if (p2 > 0 && p2 <= REG_SIZE)
	{
		champ->reg[p2 - 1] = (cor->map[(ori + p1) % MEM_SIZE] << 24) +
			(cor->map[(ori + p1 + 1) % MEM_SIZE] << 16) +
			(cor->map[(ori + p1 + 2) % MEM_SIZE] << 8) +
			cor->map[(ori + p1 + 3) % MEM_SIZE];
		if (champ->reg[p2 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_st(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 3);
	p2 = recup_content(cor, champ, ocp, 4, 3);
	if (p1 > 0 && p1 <= REG_SIZE)
	{
		if (((ocp >> 4) & 3) == REG_CODE)
		{
			if (p2 > 0 && p2 <= REG_SIZE)
				champ->reg[p2 - 1] = champ->reg[p1 - 1];
		}
		else
		{
			p2 = p2 % IDX_MOD;
			cor->map[(ori + p2) % MEM_SIZE] = champ->reg[p1 - 1] >> 24;
			cor->map[(ori + p2 + 1) % MEM_SIZE] = champ->reg[p1 - 1] >> 16;
			cor->map[(ori + p2 + 2) % MEM_SIZE] = champ->reg[p1 - 1] >> 8;
			cor->map[(ori + p2 + 3) % MEM_SIZE] = champ->reg[p1 - 1];
			if (cor->opt->v)
			{
				attron(COLOR_PAIR(2 + champ->id) | A_BOLD);
				draw_uchar((ori + p2) % MEM_SIZE, champ->reg[p1 - 1] >> 24);
				draw_uchar((ori + p2 + 1) % MEM_SIZE, champ->reg[p1 - 1] >> 16);
				draw_uchar((ori + p2 + 2) % MEM_SIZE, champ->reg[p1 - 1] >> 8);
				draw_uchar((ori + p2 + 3) % MEM_SIZE, champ->reg[p1 - 1]);
				attroff(A_BOLD);
			}
		}
		if (champ->reg[p1 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_add(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 4);
	p2 = recup_content(cor, champ, ocp, 4, 4);
	p3 = recup_content(cor, champ, ocp, 2, 4);
	if (p1 > 0 && p1 <= REG_SIZE && p2 > 0 && p2 <= REG_SIZE && p3 > 0 && p3 <= REG_SIZE)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] + champ->reg[p2 - 1];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_sub(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 4);
	p2 = recup_content(cor, champ, ocp, 4, 4);
	p3 = recup_content(cor, champ, ocp, 2, 4);
	if (p1 > 0 && p1 <= REG_SIZE && p2 > 0 && p2 <= REG_SIZE && p3 > 0 && p3 <= REG_SIZE)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] - champ->reg[p2 - 1];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
