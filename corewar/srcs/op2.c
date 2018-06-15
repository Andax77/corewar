/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:07 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:55:30 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_and(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;

	ocp = cor->map[++champ->pc];
	p1 = recup_content(cor, champ, ocp, 6, 6);
	p2 = recup_content(cor, champ, ocp, 4, 6);
	p3 = recup_content(cor, champ, ocp, 2, 6);
	if (((ocp >> 6) & 3) == REG_CODE)
		p1 = champ->reg[p1 - 1];
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = champ->reg[p2 - 1];
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
	++champ->pc;
}

void	ft_or(t_cor *cor, t_champ *champ)
{
	int r1;
	int r2;
	int r3;

}

void	ft_xor(t_cor *cor, t_champ *champ)
{
	int r1;
	int r2;
	int r3;

}

void	ft_zjmp(t_cor *cor, t_champ *champ)
{
	int p;

	p = (cor->map[++champ->pc] << 8) + cor->map[++champ->pc];
	if (champ->carry == 1)
		champ->pc = (champ->pc + p) % MEM_SIZE;// - 1;// -1 pour le ++pc dans cycle
}

void	ft_ldi(t_cor *cor, t_champ *champ)
{
	int v1;
	int v2;
	int r1;

}
