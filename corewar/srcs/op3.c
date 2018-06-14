/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:12 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/14 19:38:00 by pmilan           ###   ########.fr       */
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
	ocp = champ->splited_prog[++champ->pc];
	p1 = recup_content(champ, ocp, 6, 11);
	p2 = recup_content(champ, ocp, 4, 11);
	p3 = recup_content(champ, ocp, 2, 11);
	if (((ocp >> 4) & 3) == REG_CODE)
		p2 = champ->reg[p2 - 1];
	if (((ocp >> 2) & 3) == REG_CODE)
		p3 = champ->reg[p3 - 1];
	champ->splited_prog[((ori + p2 + p3) < 0) ? MEM_SIZE - ((ori + p2 + p3) % MEM_SIZE) : ori + p2 + p3] = champ->reg[p1 - 1];
	if (champ->reg[p1 - 1] == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
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
