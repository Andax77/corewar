/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:12 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/24 12:05:09 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_sti(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 11);
	p2 = recup_content(cor, champ, ocp, 4, 11);
	p3 = recup_content(cor, champ, ocp, 2, 11);
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_SIZE) ? champ->reg[p2 - 1] : 0;
	if (((ocp >> 2) & 3) == REG_CODE)
		p3 = (p3 > 0 && p3 <= REG_SIZE) ? champ->reg[p3 - 1] : 0;
	if (p1 > 0 && p1 <= REG_SIZE)
	{
		cor->map[ori + ((ori + p2 + p3) % MEM_SIZE - ori) % IDX_MOD] = champ->reg[p1 - 1] >> 24;
		cor->map[ori + ((ori + p2 + p3 + 1) % MEM_SIZE - ori) % IDX_MOD] = champ->reg[p1 - 1] >> 16;
		cor->map[ori + ((ori + p2 + p3 + 2) % MEM_SIZE - ori) % IDX_MOD] = champ->reg[p1 - 1] >> 8;
		cor->map[ori + ((ori + p2 + p3 + 3) % MEM_SIZE - ori) % IDX_MOD] = champ->reg[p1 - 1];
		if (cor->opt->v)
		{
			attron(COLOR_PAIR(2 + champ->id) | A_BOLD);
			draw_uchar(ori + ((ori + p2 + p3) % MEM_SIZE - ori) % IDX_MOD, champ->reg[p1 - 1] >> 24);
			draw_uchar(ori + ((ori + p2 + p3 + 1) % MEM_SIZE - ori) % IDX_MOD, champ->reg[p1 - 1] >> 16);
			draw_uchar(ori + ((ori + p2 + p3 + 2) % MEM_SIZE - ori) % IDX_MOD, champ->reg[p1 - 1] >> 8);
			draw_uchar(ori + ((ori + p2 + p3 + 3) % MEM_SIZE - ori) % IDX_MOD, champ->reg[p1 - 1]);
			attroff(A_BOLD);
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

void	ft_fork(t_cor *cor, t_champ *champ)
{
	int		p;
	int		pc;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	pc = ori + ((ori + p) % MEM_SIZE - ori) % IDX_MOD;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v)
	{
		if (check_live_value(cor, pc, champ->v_id))
		{
			attron(COLOR_PAIR(40 + champ->id));
			draw_uchar(pc, cor->map[pc]);
		}
		else
		{
			attron(COLOR_PAIR(20 + champ->id));
			draw_uchar(pc, cor->map[pc]);
		}
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
	if (p2 > 0 && p2 <= REG_SIZE)
	{
		if (((ocp >> 6) & 3) == REG_CODE)
			champ->reg[p2 - 1] = p1;
		else
		{
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
		p1 = (p1 > 0 && p1 <= REG_SIZE) ? champ->reg[p1 - 1] : 0;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_SIZE) ? champ->reg[p2 - 1] : 0;
	if (p3 > 0 && p3 <= REG_SIZE)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + p1 + p2) % MEM_SIZE] << 24) +
		(cor->map[(ori + p1 + p2 + 1) % MEM_SIZE] << 16) +
		(cor->map[(ori + p1 + p2 + 2) % MEM_SIZE] << 8) +
		cor->map[(ori + p1 + p2 + 3) % MEM_SIZE];
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
	int		p;
	int		pc;
	int		ori;

	ori = champ->pc;
	//ft_printf("{magenta}->%d{eoc}\n", ori);// 1 ligne = 64//////////////////print
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	//ft_printf("{magenta}->%d{eoc}\n", p);////////////////////////////////print
	pc = (ori + p) % MEM_SIZE;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v)
	{
		if (check_live_value(cor, pc, champ->v_id))
		{
			attron(COLOR_PAIR(40 + champ->id));
			draw_uchar(pc, cor->map[pc]);
		}
		else
		{
			attron(COLOR_PAIR(20 + champ->id));
			draw_uchar(pc, cor->map[pc]);
		}
	}
}
