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
	int p1;
	int p2;
	int p3;
	// int	t_v1;
	// int	t_v2;
	// int	size_dir;
	int	ocp;

	ocp = champ->splited_prog[champ->(++index)];
	p1 = recup_content(champ, ocp, 6, 11);
	p2 = recup_content(champ, ocp, 4, 11);
	p3 = recup_content(champ, ocp, 2, 11);
	// t_v1 = (ocp >> 4) & 3;
	// if (t_v1 == REG_CODE)
	// {
	// 	v1 = champ->splited_prog[champ->(++index)];
	// }
	// else if (t_v1 == DIR_CODE)
	// {
	// 	v1 = 0;
	// 	if (size_dir == 4)
	// 	{
	// 		v1 = champ->splited_prog[champ->(++index)] << 24 +
	// 			champ->splited_prog[champ->(++index)] << 16;
	// 	}
	// 	v1 += champ->splited_prog[champ->(++index)] << 8 +
	// 		champ->splited_prog[champ->(++index)];
	// }
	// else
	// {
	// 	v1 = //indirect
	// }
	// t_v2 = (ocp >> 2) & 3;
	// if (t_v2 == REG_CODE)
	// {
	// 	v2 = champ->splited_prog[champ->(++index)];
	// }
	// else if (t_v2 == DIR_CODE)
	// {
	// 	if (size_dir == 2)
	// 	{
	// 		v2 =
	// 	}
	// 	else
	// 	{
	// 		v2 =
	// 	}
	// }
	// else
	// {
	// 	v2 = //indirect
	// }

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
