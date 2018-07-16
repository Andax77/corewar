/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 19:54:31 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/14 11:39:20 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	ft_ld_elseif(t_cor *cor, t_champ *champ, int p1, long long p2_ori)
{
	p1 = ((short)p1 % IDX_MOD) % MEM_SIZE;
	if ((ft_get2arg(p2_ori, 1) + p1) < 0)
		p1 += MEM_SIZE;
	champ->reg[ft_get2arg(p2_ori, 0) - 1] = \
(cor->map[(ft_get2arg(p2_ori, 1) + p1) % MEM_SIZE] << 24) + \
(cor->map[(ft_get2arg(p2_ori, 1) + p1 + 1) % MEM_SIZE] << 16) + \
(cor->map[(ft_get2arg(p2_ori, 1) + p1 + 2) % MEM_SIZE] << 8) + \
cor->map[(ft_get2arg(p2_ori, 1) + p1 + 3) % MEM_SIZE];
}

void		ft_ld(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 2));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 2));
	if ((ocp == 0xD0 || ocp == 0x90)
	&& ((ocp >> 4) & 3) == REG_CODE && (((ocp >> 6) & 3) == DIR_CODE
	|| ((ocp >> 6) & 3) == IND_CODE) && p2 > 0 && p2 <= REG_NUMBER)
	{
		if (((ocp >> 6) & 3) == DIR_CODE)
			champ->reg[p2 - 1] = p1;
		else if (((ocp >> 6) & 3) == IND_CODE)
			ft_ld_elseif(cor, champ, p1, ft_2arg(p2, ori));
		champ->carry = (champ->reg[p2 - 1] == 0) ? 1 : 0;
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

static void	ft_st_optv(t_cor *cor, t_champ *champ, int p2, long long p1_ori)
{
	int		i;

	i = -1;
	if (champ->last_st && !cor->opt->d)
		while (++i < 4)
		{
			attron(COLOR_PAIR(cor->c_map[(champ->last_st_pc + i) % MEM_SIZE]));
			draw_uchar((champ->last_st_pc + i) % MEM_SIZE, \
					cor->map[(champ->last_st_pc + i) % MEM_SIZE]);
		}
	if (!cor->opt->d)
	{
		attron(COLOR_PAIR(2 + champ->id) | A_BOLD);
		draw_uchar((ft_get2arg(p1_ori, 1) + p2) % MEM_SIZE, \
				champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 24);
		draw_uchar((ft_get2arg(p1_ori, 1) + p2 + 1) % MEM_SIZE, \
				champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 16);
		draw_uchar((ft_get2arg(p1_ori, 1) + p2 + 2) % MEM_SIZE, \
				champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 8);
		draw_uchar((ft_get2arg(p1_ori, 1) + p2 + 3) % MEM_SIZE, \
				champ->reg[ft_get2arg(p1_ori, 0) - 1]);
		attroff(A_BOLD);
	}
	champ->last_st = 1;
	champ->last_st_pc = (ft_get2arg(p1_ori, 1) + p2) % MEM_SIZE;
}

static void	ft_st_elseif(t_cor *cor, t_champ *champ, int p2, long long p1_ori)
{
	p2 = ((short)p2 % IDX_MOD) % MEM_SIZE;
	if ((ft_get2arg(p1_ori, 1) + p2) < 0)
		p2 += MEM_SIZE;
	cor->map[(ft_get2arg(p1_ori, 1) + p2) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 24;
	cor->map[(ft_get2arg(p1_ori, 1) + p2 + 1) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 16;
	cor->map[(ft_get2arg(p1_ori, 1) + p2 + 2) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 8;
	cor->map[(ft_get2arg(p1_ori, 1) + p2 + 3) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1];
	if (cor->opt->v)
		ft_st_optv(cor, champ, p2, p1_ori);
	cor->c_map[(ft_get2arg(p1_ori, 1) + p2) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p2 + 1) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p2 + 2) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p2 + 3) % MEM_SIZE] = champ->id + 2;
}

void		ft_st(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 3));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 3));
	if ((ocp == 0x50 || ocp == 0x70)
	&& ((ocp >> 6) & 3) == REG_CODE && p1 > 0 && p1 <= REG_NUMBER)
	{
		if (((ocp >> 4) & 3) == REG_CODE && p2 > 0 && p2 <= REG_NUMBER)
			champ->reg[p2 - 1] = champ->reg[p1 - 1];
		else if (((ocp >> 4) & 3) == IND_CODE)
			ft_st_elseif(cor, champ, p2, ft_2arg(p1, ori));
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
