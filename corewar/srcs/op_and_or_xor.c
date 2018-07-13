/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:22:19 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/13 14:48:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_and(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 6));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 6));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 6));
	if (ft_change_sh_p1_p2(champ, ocp, &p1, &p2) == ERROR)
		return ;
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 & p2;
		champ->carry = ((p1 & p2) == 0) ? 1 : 0;
	//	champ->carry = 1;
	}
	//else
	//	champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_or(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 7));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 7));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 7));
	if (ft_change_sh_p1_p2(champ, ocp, &p1, &p2) == ERROR)
		return ;
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 | p2;
		champ->carry = ((p1 | p2) == 0) ? 1 : 0;
	//	champ->carry = 1;
	}
	//else
	//	champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_xor(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 8));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 8));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 8));
	if (ft_change_sh_p1_p2(champ, ocp, &p1, &p2) == ERROR)
		return ;
	if (((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = p1 ^ p2;
		champ->carry = ((p1 ^ p2) == 0) ? 1 : 0;
	//	champ->carry = 1;
	}
	//else
	//	champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
