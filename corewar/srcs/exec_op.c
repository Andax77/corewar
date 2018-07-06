/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/30 12:52:01 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		change_r_cy(t_cor *cor, t_champ *champ)
{
	if (cor->map[champ->pc] <= 0 || cor->map[champ->pc] > 16)
		return (1);
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

int		recup_content(t_cor *cor, t_champ *champ, int ocp, long long dec_op)
{
	int		type;
	int		ret;

	ret = 0;
	type = (ocp >> ft_get2arg(dec_op, 0)) & 3;
	if (type == REG_CODE)
		ret = cor->map[++champ->pc % MEM_SIZE];
	else if (type == DIR_CODE)
	{
		if (g_op_tab[ft_get2arg(dec_op, 1) - 1].dir_size == 0)
			ret = ((cor->map[++champ->pc % MEM_SIZE] << 24) + \
(cor->map[++champ->pc % MEM_SIZE] << 16));
		ret += ((cor->map[++champ->pc % MEM_SIZE] << 8) + \
cor->map[++champ->pc % MEM_SIZE]);
	}
	else if (type == IND_CODE)
		ret = (short)((cor->map[++champ->pc % MEM_SIZE] << 8) + \
cor->map[++champ->pc % MEM_SIZE]);
	return (ret);
}
