/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:12 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/27 00:47:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_sti(t_cor *cor, t_champ *champ)
{
	int		p1;
	short	p2;
	short	p3;
	int		ocp;
	int		ori;
	int		i;

	i = -1;
	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 11);
	p2 = recup_content(cor, champ, ocp, 4, 11);
	p3 = recup_content(cor, champ, ocp, 2, 11);
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	if (((ocp >> 2) & 3) == REG_CODE)
		p3 = (p3 > 0 && p3 <= REG_NUMBER) ? champ->reg[p3 - 1] : 0;
	p3 = ((p2 + p3) % IDX_MOD) % MEM_SIZE;
	if ((p3 + ori) < 0)
		p3 += MEM_SIZE;
	if (p1 > 0 && p1 <= REG_NUMBER)
	{
		cor->map[(ori + p3) % MEM_SIZE] = champ->reg[p1 - 1] >> 24;
		cor->map[(ori + p3 + 1) % MEM_SIZE] = champ->reg[p1 - 1] >> 16;
		cor->map[(ori + p3 + 2) % MEM_SIZE] = champ->reg[p1 - 1] >> 8;
		cor->map[(ori + p3 + 3) % MEM_SIZE] = champ->reg[p1 - 1];
		if (cor->opt->v)
		{
			if (champ->last_st)
				while (++i < 4)
				{
					attron(COLOR_PAIR(cor->c_map[champ->last_st_pc + i]));
					draw_uchar(champ->last_st_pc + i, cor->map[champ->last_st_pc + i]);
				}
			attron(COLOR_PAIR(2 + champ->id) | A_BOLD);
			draw_uchar((ori + p3) % MEM_SIZE, champ->reg[p1 - 1] >> 24);
			cor->c_map[(ori + p3) % MEM_SIZE] = champ->id + 2;
			draw_uchar((ori + p3 + 1) % MEM_SIZE, champ->reg[p1 - 1] >> 16);
			cor->c_map[(ori + p3 + 1) % MEM_SIZE] = champ->id + 2;
			draw_uchar((ori + p3 + 2) % MEM_SIZE, champ->reg[p1 - 1] >> 8);
			cor->c_map[(ori + p3 + 2) % MEM_SIZE] = champ->id + 2;
			draw_uchar((ori + p3 + 3) % MEM_SIZE, champ->reg[p1 - 1]);
			cor->c_map[(ori + p3 + 3) % MEM_SIZE] = champ->id + 2;
			attroff(A_BOLD);
			champ->last_st = 1;
			champ->last_st_pc = (ori + p3) % MEM_SIZE;
		}
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_fork(t_cor *cor, t_champ *champ)
{
	short	p;
	int		pc;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	pc = ori + ((p % IDX_MOD) % MEM_SIZE);
	if (pc < 0)
		pc += MEM_SIZE;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v)
	{
		attron(COLOR_PAIR(20 + champ->id));
		draw_uchar(pc, cor->map[pc]);
	}
}

void	ft_lld(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 13);
	p2 = recup_content(cor, champ, ocp, 4, 13);
	if (p2 > 0 && p2 <= REG_NUMBER)
	{
		if (((ocp >> 6) & 3) == REG_CODE)
			champ->reg[p2 - 1] = p1;
		else
		{
			p1 = (short)p1 % MEM_SIZE;
			if ((ori + p1) < 0)
				p1 += MEM_SIZE;
			champ->reg[p2 - 1] = (cor->map[(ori + p1) % MEM_SIZE] << 24) +
				(cor->map[(ori + p1 + 1) % MEM_SIZE] << 16) +
				(cor->map[(ori + p1 + 2) % MEM_SIZE] << 8) +
				cor->map[(ori + p1 + 3) % MEM_SIZE];
		}
		if (champ->reg[p2 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_lldi(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 14);
	p2 = recup_content(cor, champ, ocp, 4, 14);
	p3 = recup_content(cor, champ, ocp, 2, 14);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = (p1 > 0 && p1 <= REG_NUMBER) ? champ->reg[p1 - 1] : 0;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	p2 = (p1 + p2) % MEM_SIZE;
	if ((p2 + ori) < 0)
		p2 += MEM_SIZE;
	if (p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + p2) % MEM_SIZE] << 24) +
		(cor->map[(ori + p2 + 1) % MEM_SIZE] << 16) +
		(cor->map[(ori + p2 + 2) % MEM_SIZE] << 8) +
		cor->map[(ori + p2 + 3) % MEM_SIZE];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_lfork(t_cor *cor, t_champ *champ)
{
	short	p;
	int		pc;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	pc = (ori + p) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v)
	{
		attron(COLOR_PAIR(20 + champ->id));
		draw_uchar(pc, cor->map[pc]);
	}
}
