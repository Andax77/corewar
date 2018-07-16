/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp_fork_lfork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:24:52 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 16:12:24 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_zjmp(t_cor *cor, t_champ *champ)
{
	short	p;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc
		% MEM_SIZE];
	if (champ->carry == 1)
	{
		champ->pc = ((ori + (p % IDX_MOD)) % MEM_SIZE);
		if (champ->pc < 0)
			champ->pc += MEM_SIZE;
	}
	else
		champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_fork(t_cor *cor, t_champ *champ)
{
	short	p;
	int		pc;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8)
		+ cor->map[++champ->pc % MEM_SIZE];
	pc = (ori + (p % IDX_MOD)) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v && !cor->opt->d)
	{
		attron(COLOR_PAIR(20 + champ->id));
		draw_uchar(pc, cor->map[pc]);
	}
}

void		ft_lfork(t_cor *cor, t_champ *champ)
{
	short	p;
	int		pc;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8)
		+ cor->map[++champ->pc % MEM_SIZE];
	pc = (ori + p) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	legacy(cor, champ, champ->id, pc);
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (cor->opt->v && !cor->opt->d)
	{
		attron(COLOR_PAIR(20 + champ->id));
		draw_uchar(pc, cor->map[pc]);
	}
}
