/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/14 17:38:35 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <corewar.h>

/*
The launcher during *** times for VM
*/
//add stop_vm in 1st while
void	cycle(t_cor *cor)
{
	t_list		*champs;
	t_list		*first_champ;
	t_champ		*cur_champ;
	int			last_pc;
	t_champ		*last_champ;

	last_pc = 0;
	champs = cor->champs;
	first_champ = champs;
	while ((champs = first_champ))
	{
		while (champs)
		{
			cur_champ = champs->content;
			last_champ = cur_champ;
			if (cur_champ->r_cy > -1)
			{
				if (cur_champ->r_cy == 0)
				{
					//exec_op(cor, &cur_champ);
					//He would send a OPcode to exec_op
					if (cor->opt->n)
					{
						//attron(COLOR_PAIR((last_champ->reg)[0]));
						//draw_uchar(cur_champ->pc, (cor->map)[last_pc]);
						attron(COLOR_PAIR(10 + (cur_champ->reg)[0]));
						draw_uchar(cur_champ->pc, (cor->map)[cur_champ->pc]);
						getch();
					}
					//ft_printf("cur_champ = %s, cur_pc = %d\n", cur_champ->name, cur_champ->pc);
					last_pc = cur_champ->pc;
					last_champ = cur_champ;
					if (cur_champ->pc < MEM_SIZE)
						cur_champ->pc++;
					else
						cur_champ->pc = 0;
				}
				else
					(cur_champ->r_cy)--;
			}
			champs = champs->next;
		}
		(cor->cycle)++;
	}
}

/*
Array of Pointer in function for replace the "Forest of if"
*/
/*
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
*/
/*
To recup the register or the index value from all operators :)
*/
/*
int		recup_content(t_champ *champ, int ocp, int decalage, int op_code)
{
	int ocp;
	int type;
	int ret;

	ret = 0;
	type = (ocp >> decalage) & 3;
	if (type == REG_CODE)
	{
		ret = champ->reg[champ->splited_prog[champ->(++index)] - 1];
	}
	else if (type == DIR_CODE)
	{
		if (((g_op_tab[op_code - 1].dir_size == 1) ? 2 : 4) == 4)
			ret = champ->splited_prog[champ->(++index)] << 24 +
				champ->splited_prog[champ->(++index)] << 16;
		ret += champ->splited_prog[champ->(++index)] << 8 +
			champ->splited_prog[champ->(++index)];
	}
	else
		ret = champ->splited_prog[champ->(++index)] << 8 +
			champ->splited_prog[champ->(++index)];
	return (ret);
}
*/
/*
The last OPcode function(I don't where to place it so here, I think is good)
*/
/*
void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}
*/
