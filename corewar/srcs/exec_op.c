/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/25 17:45:41 by eparisot         ###   ########.fr       */
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

int		recup_content(t_cor *cor, t_champ *champ, int ocp, int decalage, int op_code)
{
	int type;
	int ret;

	ret = 0;
	type = (ocp >> decalage) & 3;
	if (type == REG_CODE)
	{
		ret = cor->map[++champ->pc % MEM_SIZE];
	}
	else if (type == DIR_CODE)
	{
		if (g_op_tab[op_code - 1].dir_size == 0)
			ret = ((cor->map[++champ->pc % MEM_SIZE] << 24) + (cor->map[++champ->pc % MEM_SIZE] << 16));
		ret += ((cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE]);
	}
	else
		ret = (cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	return (ret);
}

static void	ft_aff_next(t_cor *cor, t_champ *champ, char *str)
{
	if (champ->id == 1)
		if (!(cor->aff = ft_str_and_free_join(cor->aff, "{red}")))
			exit(EXIT_FAILURE);
	if (champ->id == 2)
		if (!(cor->aff = ft_str_and_free_join(cor->aff, "{green}")))
			exit(EXIT_FAILURE);
	if (champ->id == 3)
		if (!(cor->aff = ft_str_and_free_join(cor->aff, "{yellow}")))
			exit(EXIT_FAILURE);
	if (champ->id == 4)
		if (!(cor->aff = ft_str_and_free_join(cor->aff, "{blue}")))
			exit(EXIT_FAILURE);
	if (!(cor->aff = ft_str_and_free_join(cor->aff, champ->name)))
		exit(EXIT_FAILURE);
	if (!(cor->aff = ft_str_and_free_join(cor->aff, " : ")))
		exit(EXIT_FAILURE);
	if (!(cor->aff = ft_str_and_free_join(cor->aff, str)))
		exit(EXIT_FAILURE);
	if (!(cor->aff = ft_str_and_free_join(cor->aff, "\n")))
		exit(EXIT_FAILURE);
	if (!(cor->aff = ft_str_and_free_join(cor->aff, "{eoc}")))
		exit(EXIT_FAILURE);
}

void	ft_aff(t_cor *cor, t_champ *champ)
{
	int		p;
	char	*str;

	champ->pc = (champ->pc + 1) % MEM_SIZE;
	p = cor->map[++champ->pc % MEM_SIZE];
	if (p > 0 && p <= REG_SIZE)
	{
		if (cor->aff == NULL)
			if (!(cor->aff = ft_strnew(1)))
				exit(EXIT_FAILURE);
		if (!(str = ft_strnew(2)))
			exit(EXIT_FAILURE);
		str[0] = champ->reg[p - 1] % 256;
		ft_aff_next(cor, champ, str);
		free(str);
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_move(t_cor *cor, t_champ *champ)
{
	(void)cor;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
