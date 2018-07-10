/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 21:22:18 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/10 13:13:23 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	ft_change_sh_p2_p3(t_champ *champ, int ocp, int *p2, int *p3)
{
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
	if (((ocp >> 2) & 3) == REG_CODE)
	{
		if (*p3 > 0 && *p3 <= REG_NUMBER)
			*p3 = champ->reg[*p3 - 1];
		else
		{
			champ->pc = (champ->pc + 1) % MEM_SIZE;
			return (ERROR);
		}
	}
	else
		*p3 = (short)*p3;
	return (SUCCESS);
}

static void	ft_sti_optv(t_cor *cor, t_champ *champ, short p3, long long p1_ori)
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
		draw_uchar((ft_get2arg(p1_ori, 1) + p3) % MEM_SIZE, \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 24);
		draw_uchar((ft_get2arg(p1_ori, 1) + p3 + 1) % MEM_SIZE, \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 16);
		draw_uchar((ft_get2arg(p1_ori, 1) + p3 + 2) % MEM_SIZE, \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 8);
		draw_uchar((ft_get2arg(p1_ori, 1) + p3 + 3) % MEM_SIZE, \
champ->reg[ft_get2arg(p1_ori, 0) - 1]);
		attroff(A_BOLD);
	}
	champ->last_st = 1;
	champ->last_st_pc = (ft_get2arg(p1_ori, 1) + p3) % MEM_SIZE;
}

static void	ft_sti_if(t_cor *cor, t_champ *champ, short p3, long long p1_ori)
{
	cor->map[(ft_get2arg(p1_ori, 1) + p3) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 24;
	cor->map[(ft_get2arg(p1_ori, 1) + p3 + 1) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 16;
	cor->map[(ft_get2arg(p1_ori, 1) + p3 + 2) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1] >> 8;
	cor->map[(ft_get2arg(p1_ori, 1) + p3 + 3) % MEM_SIZE] = \
champ->reg[ft_get2arg(p1_ori, 0) - 1];
	if (cor->opt->v)
		ft_sti_optv(cor, champ, p3, p1_ori);
	cor->c_map[(ft_get2arg(p1_ori, 1) + p3) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p3 + 1) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p3 + 2) % MEM_SIZE] = champ->id + 2;
	cor->c_map[(ft_get2arg(p1_ori, 1) + p3 + 3) % MEM_SIZE] = champ->id + 2;
}

void	ft_sti(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 11));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 11));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 11));
	if (ft_change_sh_p2_p3(champ, ocp, &p2, &p3) == ERROR)
		return ;
	p3 = ((p2 + p3) % IDX_MOD) % MEM_SIZE;
	if ((p3 + ori) < 0)
		p3 += MEM_SIZE;
	if ((((ocp >> 2) & 3) == DIR_CODE || ((ocp >> 2) & 3) == REG_CODE) && \
((ocp >> 6) & 3) == REG_CODE && p1 > 0 && p1 <= REG_NUMBER)
		ft_sti_if(cor, champ, p3, ft_2arg(p1, ori));
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
