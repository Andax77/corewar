/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_move_add_sub_aff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 22:02:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/13 19:11:03 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_move(t_cor *cor, t_champ *champ)
{
	(void)cor;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	champ->cur_op = 0;
}

void		ft_add(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 4));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 4));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 4));
	if (((ocp >> 6) & 3) == REG_CODE && ((ocp >> 4) & 3) == REG_CODE
			&& ((ocp >> 2) & 3) == REG_CODE && p1 > 0 && p1 <= REG_NUMBER
			&& p2 > 0 && p2 <= REG_NUMBER && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] + champ->reg[p2 - 1];
		champ->carry = (champ->reg[p3 - 1] == 0) ? 1 : 0;
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void		ft_sub(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		p3;
	int		ocp;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, ft_2arg(6, 4));
	p2 = recup_content(cor, champ, ocp, ft_2arg(4, 4));
	p3 = recup_content(cor, champ, ocp, ft_2arg(2, 4));
	if (((ocp >> 6) & 3) == REG_CODE && ((ocp >> 4) & 3) == REG_CODE
			&& ((ocp >> 2) & 3) == REG_CODE && p1 > 0 && p1 <= REG_NUMBER
			&& p2 > 0 && p2 <= REG_NUMBER && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] - champ->reg[p2 - 1];
		champ->carry = (champ->reg[p3 - 1] == 0) ? 1 : 0;
	}
	champ->pc = (champ->pc + 1) % MEM_SIZE;
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

void		ft_aff(t_cor *cor, t_champ *champ)
{
	int		p;
	int		ocp;
	char	*str;

	ocp = cor->map[++champ->pc % MEM_SIZE];
	p = recup_content(cor, champ, ocp, ft_2arg(6, 16));
	if (((ocp >> 6) & 3) == REG_CODE && p > 0 && p <= REG_SIZE)
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
