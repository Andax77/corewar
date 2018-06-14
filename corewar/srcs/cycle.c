/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 01:08:48 by eparisot         ###   ########.fr       */
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
	int			last_champ;
	//void		(*f[17])(t_cor *cor, t_champ *cur_champ);

	//init_op(f);
	last_pc = 0;
	last_champ = 0;
	champs = cor->champs;
	first_champ = champs;
	while ((champs = first_champ))
	{
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				if (cur_champ->r_cy == 0)
				{
					//f[cur_champ->splited_prog[cur_champ->pc]](cor, cur_champ);// faire un if pour f[0] si op_code invalide/////////////////
					//He would send a OPcode to exec_op
					if (cor->opt->n)
					{
						if (last_champ)
						{
							attron(COLOR_PAIR(2 + last_champ));
							draw_uchar(last_pc, (cor->map)[last_pc]);
						}
						attron(COLOR_PAIR(10 + cur_champ->reg[0]));
						draw_uchar(cur_champ->pc, (cor->map)[cur_champ->pc]);
						getch();
					}
					//ft_printf("cur_champ = %s, cur_pc = %d\n", cur_champ->name, cur_champ->pc);
					last_pc = cur_champ->pc;
					last_champ = cur_champ->reg[0];
					if (cur_champ->pc < MEM_SIZE)
						cur_champ->pc++;
					else
						cur_champ->pc = ((t_champ*)champs->content)->pc;
				}
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		(cor->cycle)++;
	}
}
/*
//Array of Pointer in function for replace the "Forest of if"

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

//To recup the register or the index value from all operators :)


int		recup_content(t_champ *champ, int ocp, int decalage, int op_code)
{
	int type;
	int ret;

	ret = 0;
	type = (ocp >> decalage) & 3;
	if (type == REG_CODE)
	{
		ret = champ->splited_prog[++champ->pc];
	}
	else if (type == DIR_CODE)
	{
		if (((g_op_tab[op_code - 1].dir_size == 1) ? 2 : 4) == 4)
			ret = (champ->splited_prog[++champ->pc] << 24) +
				(champ->splited_prog[++champ->pc] << 16);
		ret += (champ->splited_prog[++champ->pc] << 8) +
			champ->splited_prog[++champ->pc];
	}
	else
		ret = (champ->splited_prog[++champ->pc] << 8) +
			champ->splited_prog[++champ->pc];
	return (ret);
}

//The last OPcode function(I don't know where to place it so here, I think is good)

void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}

void	ft_move(t_cor *cor, t_champ  *champ)
{
	int r1;
}
*/
