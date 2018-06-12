/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 19:55:19 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/12 18:11:59 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	check_op(unsigned char *prog, int i)
{
	int	j;
	int	tmp_ocp;

	j = -1;
	if (g_op_tab[prog[i] - 1].modif_carry == 1)
	{
		while (++j < g_op_tab[prog[i] - 1].nb_params)
		{
			tmp_ocp = (((prog[i + 1] >> (2 * (3 - j))) & 0x3) == 3) ? 4 : \
					  (prog[i + 1] >> (2 * (3 - j))) & 0x3;
			if ((tmp_ocp & (g_op_tab[prog[i] - 1].params_type[j])) != tmp_ocp)
				return (ERROR);
		}
	}
	else
		if (prog[i] == 1 && (prog[++i] != 0 || prog[++i] != 0 || prog[++i] != 0\
				|| (prog[++i] <= 0 || prog[i] > 16)))
			return (ERROR);
	return (SUCCESS);
}

static int	parse_op(unsigned char *op)
{
	int		i;

	i = 0;
	if (op[i + 1])
	{
		if (op[i + 1] == 0x54)
			i += 5;
		else if (op[i + 1] == 0xD4 || op[i + 1] == 0x74)
			i += 6;
		else if (op[i + 1] == 0xF4)
			i += 7;
		else if (op[i + 1] == 0x94 || op[i + 1] == 0x64)
			i += 8;
		else if (op[i + 1] == 0xB4 || op[i + 1] == 0xE4)
			i += 9;
		else if (op[i + 1] == 0xA4)
			i += 11;
	}
	return (i);
}

static int	parse_op_bis(unsigned char *op)
{
	int		i;

	i = 0;
	if (op[i + 1])
	{
		if (op[i + 1] == 0x54)
			i += 5;
		else if (op[i + 1] == 0xD4 || op[i + 1] == 0x94 || op[i + 1] == 0x64)
			i += 6;
		else if (op[i + 1] == 0xE4 || op[i + 1] == 0xA4)
			i += 7;
	}
	return (i);
}

static int	parse_op_ter(unsigned char *op)
{
	int		i;

	i = 0;
	if (op[i + 1])
	{
		if (op[i + 1] == 0x54)
			i += 5;
		else if (op[i + 1] == 0x74 || op[i + 1] == 0x64 || op[i + 1] == 0x58)
		{
			i += 6;
		}
		else if (op[i + 1] == 0x78 || op[i + 1] == 0x68)
		{
			i += 7;
		}
	}
	return (i);
}

int			check_op_len(t_champ *champ)
{
	int				i;
	unsigned char	*prog;

	i = 0;
	prog = champ->splited_prog;
	while (i < champ->op_nb)
	{
		if (prog[i] > 16 || check_op(prog, i) == ERROR)
			return (ERROR);
		(prog[i] == 1 || prog[i] == 4 || prog[i] == 5) ? i += 5 : 0;
		((prog[i] == 2 || prog[i] == 13) && prog[i + 1] == 0xD0) ? i += 5 : 0;
		((prog[i] == 2 || prog[i] == 13) && prog[i + 1] == 0x90) ? i += 7 : 0;
		(prog[i] == 3 && prog[i + 1] == 0x50) ? i += 4 : 0;
		(prog[i] == 3 && prog[i + 1] == 0x70) ? i += 5 : 0;
		if (prog[i] == 6 || prog[i] == 7 || prog[i] == 8)
			i += parse_op(&prog[i]);
		if (prog[i] == 9 || prog[i] == 12 || prog[i] == 15 || prog[i] == 16)
			i += 3;
		if (prog[i] == 10 || prog[i] == 14)
			i += parse_op_bis(&prog[i]);
		if (prog[i] == 11)
			i += parse_op_ter(&prog[i]);
	}
	return (SUCCESS);
}
