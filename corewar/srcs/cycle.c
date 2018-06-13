/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/13 15:06:19 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <corewar.h>

void	cycle(t_cor *cor)
{
	t_champ *ori;
	t_list *champ;
//add stop_vm in 1st while
	champ = cor->champs;
	ori = champ;
	while ((champ = ori))
	{
		while (champ)
		{
			if (((t_champ *)champ->content)->r_cy != -1)
			{
				if (((t_champ *)champ->content)->r_cy == 0)
					exec_op(cor, &champ);
					//He would send a OPcode to exec_op
				(((t_champ *)champ->content)->r_cy)--;
			}
			champ = champ->next;
		}
		(cor->cycle)++;
	}
}

void	exec_op(t_cor *cor, t_champ **champ)
{
	void (**f)(*cor, *champ);

	f[1] = &live;
	f[2] = &ld;
	f[3] = &st;
	f[4] = &add;
	f[5] = &sub;
	f[6] = &f_and;
	f[7] = &f_or;
	f[8] = &f_xor;
	f[9] = &ft_zjmp;
	f[10] = &ldi;
	f[11] = &sti;
	f[12] = &ft_fork;
	f[13] = &lld;
	f[14] = &lldi;
	f[15] = &lfork;
	f[16] = &ft_aff;
}

int		recup_content(t_champ *champ)
{
	int ocp;
	int type;
	int ret;

	ocp = champ->splited_prog[champ->(++index)];
	type = (ocp >> 4) & 3;
	if (type == REG_CODE)
	{
		ret = champ->splited_prog[champ->(++index)];
	}
	else if (t_v1 == DIR_CODE)
	{
		ret = 0;
		if (size_dir == 4)
		{
			ret = champ->splited_prog[champ->(++index)] << 24 +
				champ->splited_prog[champ->(++index)] << 16;
		}
		ret += champ->splited_prog[champ->(++index)] << 8 +
			champ->splited_prog[champ->(++index)];
	}
	else
		ret = -1;//indirect
	return (ret);
}

void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}









































z
