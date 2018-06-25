/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:07 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/25 10:49:15 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_and(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 6);
	p2 = recup_content(cor, champ, ocp, 4, 6);
	p3 = recup_content(cor, champ, ocp, 2, 6);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = (p1 > 0 && p1 <= REG_NUMBER) ? champ->reg[p1 - 1] : 0;
	else
		p1 = p1 % IDX_MOD;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	else
		p2 = p2 % IDX_MOD;
	if (p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 & p2;
		if ((p1 & p2) == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_or(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 7);
	p2 = recup_content(cor, champ, ocp, 4, 7);
	p3 = recup_content(cor, champ, ocp, 2, 7);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = (p1 > 0 && p1 <= REG_NUMBER) ? champ->reg[p1 - 1] : 0;
	else
		p1 = p1 % IDX_MOD;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	else
		p2 = p2 % IDX_MOD;
	if (p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 | p2;
		if ((p1 | p2) == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_xor(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 8);
	p2 = recup_content(cor, champ, ocp, 4, 8);
	p3 = recup_content(cor, champ, ocp, 2, 8);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = (p1 > 0 && p1 <= REG_NUMBER) ? champ->reg[p1 - 1] : 0;
	else
		p1 = p1 % IDX_MOD;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	else
		p2 = p2 % IDX_MOD;
	if (p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 ^ p2;
		if ((p1 ^ p2) == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_zjmp(t_cor *cor, t_champ *champ)
{
	int p;
	int	ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	if (champ->carry == 1)
		champ->pc = ori + ((ori + p) % MEM_SIZE - ori) % IDX_MOD;
	else
		champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_ldi(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 10);
	p2 = recup_content(cor, champ, ocp, 4, 10);
	p3 = recup_content(cor, champ, ocp, 2, 10);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = (p1 > 0 && p1 <= REG_NUMBER) ? champ->reg[p1 - 1] : 0;
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = (p2 > 0 && p2 <= REG_NUMBER) ? champ->reg[p2 - 1] : 0;
	if (p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + (p1 + p2) % IDX_MOD) % MEM_SIZE] << 24) +
		(cor->map[(ori + (p1 + p2) % IDX_MOD + 1) % MEM_SIZE] << 16) +
		(cor->map[(ori + (p1 + p2) % IDX_MOD + 2) % MEM_SIZE] << 8) +
		cor->map[(ori + (p1 + p2) % IDX_MOD + 3) % MEM_SIZE];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
