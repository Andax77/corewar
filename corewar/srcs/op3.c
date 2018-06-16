/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:12 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:55:47 by pmilan           ###   ########.fr       */
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
	ocp = cor->map[++champ->pc];
	p1 = recup_content(cor, champ, ocp, 6, 11);
	p2 = recup_content(cor, champ, ocp, 4, 11);
	p3 = recup_content(cor, champ, ocp, 2, 11);
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = champ->reg[p2 - 1];
	if (((ocp >> 2) & 3) == REG_CODE)
		p3 = champ->reg[p3 - 1];
	while ((ori + p2 + p3) < 0)
		p3 += MEM_SIZE;
	cor->map[(ori + p2 + p3) % MEM_SIZE] = champ->reg[p1 - 1] >> 24;
	cor->map[(ori + p2 + p3 + 1) % MEM_SIZE] = champ->reg[p1 - 1] >> 16;
	cor->map[(ori + p2 + p3 + 2) % MEM_SIZE] = champ->reg[p1 - 1] >> 8;
	cor->map[(ori + p2 + p3 + 3) % MEM_SIZE] = champ->reg[p1 - 1];
	if (champ->reg[p1 - 1] == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
	++champ->pc;
}

void	ft_fork(t_cor *cor, t_champ *champ)
{
	int v1;

}

void	ft_lld(t_cor *cor, t_champ *champ)
{
	int r1;
	int v1;

}

void	ft_lldi(t_cor *cor, t_champ *champ)
{
	int r1;
	int v1;
	int v2;

}

void	ft_lfork(t_cor *cor, t_champ *champ)
{
	int v1;

}
