/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi_lld_lldi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:29:56 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/14 11:48:57 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			ft_change_sh_p1_p2(t_champ *champ, int ocp, int *p1, int *p2)
{
	if (((ocp >> 6) & 3) == REG_CODE)
	{
		if (*p1 > 0 && *p1 <= REG_NUMBER)
			*p1 = champ->reg[*p1 - 1];
		else
		{
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return (ERROR);
		}
	}
	else
		*p1 = (short)*p1;
	if (((ocp >> 4) & 3) == REG_CODE)
	{
		if (*p2 > 0 && *p2 <= REG_NUMBER)
			*p2 = champ->reg[*p2 - 1];
		else
		{
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return (ERROR);
		}
	}
	else
		*p2 = (short)*p2;
	return (SUCCESS);
}

void		ft_ldi(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 10));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 10));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 10));
	if (ft_change_sh_p1_p2(champ, ocp, &p1, &p2) == ERROR)
		return ;
	p2 = ((p1 + p2) % IDX_MOD) % MEM_SIZE;
	if ((p2 + ori) < 0)
		p2 += MEM_SIZE;
	if ((ocp == 0x54 || ocp == 0xD4 || ocp == 0x94 || ocp == 0x64
	|| ocp == 0xE4 || ocp == 0xA4)
	&& (((ocp >> 4) & 3) == REG_CODE || ((ocp >> 4) & 3) == DIR_CODE)
	&& ((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + p2) % MEM_SIZE] << 24)
			+ (cor->map[(ori + p2 + 1) % MEM_SIZE] << 16)
			+ (cor->map[(ori + p2 + 2) % MEM_SIZE] << 8)
			+ cor->map[(ori + p2 + 3) % MEM_SIZE];
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_lldi(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 14));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 14));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 14));
	if (ft_change_sh_p1_p2(champ, ocp, &p1, &p2) == ERROR)
		return ;
	p2 = (p1 + p2) % MEM_SIZE;
	p2 += ((p2 + ori) < 0) ? MEM_SIZE : 0;
	if ((ocp == 0x54 || ocp == 0xD4 || ocp == 0x94 || ocp == 0x64
	|| ocp == 0xE4 || ocp == 0xA4)
	&& (((ocp >> 4) & 3) == REG_CODE || ((ocp >> 4) & 3) == DIR_CODE)
	&& ((ocp >> 2) & 3) == REG_CODE && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = (cor->map[(ori + p2) % MEM_SIZE] << 24)
			+ (cor->map[(ori + p2 + 1) % MEM_SIZE] << 16)
			+ (cor->map[(ori + p2 + 2) % MEM_SIZE] << 8)
			+ cor->map[(ori + p2 + 3) % MEM_SIZE];
		champ->carry = (champ->reg[p3 - 1] == 0) ? 1 : 0;
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_lld(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 13));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 13));
	if ((ocp == 0xD0 || ocp == 0x90)
	&& ((ocp >> 4) & 3) == REG_CODE && (((ocp >> 6) & 3) == DIR_CODE
	|| ((ocp >> 6) & 3) == IND_CODE) && p2 > 0 && p2 <= REG_NUMBER)
	{
		if (((ocp >> 6) & 3) == DIR_CODE)
			champ->reg[p2 - 1] = p1;
		else if (((ocp >> 6) & 3) == IND_CODE)
		{
			p1 = (short)p1 % MEM_SIZE;
			p1 += ((ori + p1) < 0) ? MEM_SIZE : 0;
			champ->reg[p2 - 1] = (cor->map[(ori + p1) % MEM_SIZE] << 24)
			+ (cor->map[(ori + p1 + 1) % MEM_SIZE] << 16) + (cor->map[(ori
			+ p1 + 2) % MEM_SIZE] << 8) + cor->map[(ori + p1 + 3) % MEM_SIZE];
		}
		champ->carry = (champ->reg[p2 - 1] == 0) ? 1 : 0;
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
