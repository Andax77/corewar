/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/16 11:23:00 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		change_r_cy(t_cor *cor, t_champ *champ)
{
	if (cor->map[champ->pc] <= 0 || cor->map[champ->pc] > 16)
		return (0);
	else
		return (g_op_tab[cor->map[champ->pc] - 1].nb_cycles);
}

void	init_op(void (**f)(t_cor*, t_champ*))
{
	f[0] = &ft_move;
	f[1] = &ft_live;
	f[2] = &ft_ld;
	f[3] = &ft_st;
	f[4] = &ft_add;
	f[5] = &ft_sub;
	f[6] = &ft_and;
	f[7] = &ft_or;
	f[8] = &ft_xor;
	f[9] = &ft_zjmp;
	f[10] = &ft_ldi;
	f[11] = &ft_sti;
	f[12] = &ft_fork;
	f[13] = &ft_lld;
	f[14] = &ft_lldi;
	f[15] = &ft_lfork;
	f[16] = &ft_aff;
}

int		recup_content(t_cor *cor, t_champ *champ, int ocp, int decalage, int op_code)
{
	int type;
	int ret;

	ret = 0;
	type = (ocp >> decalage) & 3;
	if (type == REG_CODE)
	{
		ret = cor->map[++champ->pc];
	}
	else if (type == DIR_CODE)
	{
		if (((g_op_tab[op_code - 1].dir_size == 1) ? 2 : 4) == 4)
			ret = (cor->map[++champ->pc] << 24) + (cor->map[++champ->pc] << 16);
		ret += (cor->map[++champ->pc] << 8) + cor->map[++champ->pc];
	}
	else
		ret = (cor->map[++champ->pc] << 8) + cor->map[++champ->pc];
	return (ret);
}

void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}

void	ft_move(t_cor *cor, t_champ  *champ)
{
	int r1;
}
