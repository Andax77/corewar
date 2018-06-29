/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:07 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/29 17:59:19 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_and(t_cor *cor, t_champ *champ)//verif si need idx_mod
{
	int		p1;// shorts plutot ??///////////////////////////////////////
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 6);
	p2 = recup_content(cor, champ, ocp, 4, 6);
	p3 = recup_content(cor, champ, ocp, 2, 6);
	if (((ocp >> 6) & 3) == REG_CODE)
	{
		if (p1 > 0 && p1 <= REG_NUMBER)
			p1 = champ->reg[p1 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 4) & 3) == REG_CODE)
	{
		if (p2 > 0 && p2 <= REG_NUMBER)
			p2 = champ->reg[p2 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 & p2;
		champ->carry = ((p1 & p2) == 0) ? 1 : 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_or(t_cor *cor, t_champ *champ)//verif si need idx_mod
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 7);
	p2 = recup_content(cor, champ, ocp, 4, 7);
	p3 = recup_content(cor, champ, ocp, 2, 7);
	if (((ocp >> 6) & 3) == REG_CODE)
	{
		if (p1 > 0 && p1 <= REG_NUMBER)
			p1 = champ->reg[p1 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 4) & 3) == REG_CODE)
	{
		if (p2 > 0 && p2 <= REG_NUMBER)
			p2 = champ->reg[p2 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 | p2;
		champ->carry = ((p1 | p2) == 0) ? 1 : 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_xor(t_cor *cor, t_champ *champ)//verif si need idx_mod
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 8);
	p2 = recup_content(cor, champ, ocp, 4, 8);
	p3 = recup_content(cor, champ, ocp, 2, 8);
	if (((ocp >> 6) & 3) == REG_CODE)
	{
		if (p1 > 0 && p1 <= REG_NUMBER)
			p1 = champ->reg[p1 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 4) & 3) == REG_CODE)
	{
		if (p2 > 0 && p2 <= REG_NUMBER)
			p2 = champ->reg[p2 - 1];
		else
		{
			champ->carry = 0;
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 ^ p2;
		champ->carry = ((p1 ^ p2) == 0) ? 1 : 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_zjmp(t_cor *cor, t_champ *champ)
{
	short	p;
	int		ori;

	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % \
MEM_SIZE];
	if (champ->carry == 1)
	{
		champ->pc = ori + ((p % IDX_MOD) % MEM_SIZE);
		if (champ->pc < 0)
			champ->pc += MEM_SIZE;
	}
	else
		champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_ldi(t_cor *cor, t_champ *champ)
{
	short	p1;
	short	p2;
	int		p3;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 10);
	p2 = recup_content(cor, champ, ocp, 4, 10);
	p3 = recup_content(cor, champ, ocp, 2, 10);
	if (((ocp >> 6) & 3) == REG_CODE)
	{
		if (p1 > 0 && p1 <= REG_NUMBER)
			p1 = champ->reg[p1 - 1];
		else
		{
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (((ocp >> 4) & 3) == REG_CODE)
	{
		if (p2 > 0 && p2 <= REG_NUMBER)
			p2 = champ->reg[p2 - 1];
		else
		{
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return ;
		}
	}
	p2 = ((p1 + p2) % IDX_MOD) % MEM_SIZE;
	if ((p2 + ori) < 0)
		p2 += MEM_SIZE;
	if ((((ocp >> 4) & 3) == REG_CODE || ((ocp >> 4) & 3) == DIR_CODE) && \
((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + p2) % MEM_SIZE] << 24) + \
(cor->map[(ori + p2 + 1) % MEM_SIZE] << 16) + \
(cor->map[(ori + p2 + 2) % MEM_SIZE] << 8) + \
cor->map[(ori + p2 + 3) % MEM_SIZE];
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
