/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:12 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/13 15:06:13 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sti(t_cor *cor, t_champ *champ)
{
	int r1;
	int v1;
	int v2;
	int	t_v1;
	int	t_v2;
	int	size_dir;
	int	ocp;

	size_dir = (g_op_tab[10].dir_size == 1) ? 2 : 4;
	ocp = champ->splited_prog[champ->(++index)];
	r1 = champ->reg[champ->splited_prog[champ->(++index)] - 1];
	t_v1 = (ocp >> 4) & 3;
	if (t_v1 == REG_CODE)
	{
		v1 = champ->splited_prog[champ->(++index)];
	}
	else if (t_v1 == DIR_CODE)
	{
		v1 = 0;
		if (size_dir == 4)
		{
			v1 = champ->splited_prog[champ->(++index)] << 24 +
				champ->splited_prog[champ->(++index)] << 16;
		}
		v1 += champ->splited_prog[champ->(++index)] << 8 +
			champ->splited_prog[champ->(++index)];
	}
	else
	{
		v1 = //indirect
	}
	t_v2 = (ocp >> 2) & 3;
	if (t_v2 == REG_CODE)
	{
		v2 = champ->splited_prog[champ->(++index)];
	}
	else if (t_v2 == DIR_CODE)
	{
		if (size_dir == 2)
		{
			v2 =
		}
		else
		{
			v2 =
		}
	}
	else
	{
		v2 = //indirect
	}

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
