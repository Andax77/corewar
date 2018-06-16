/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/16 01:49:10 by eparisot         ###   ########.fr       */
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
	int			*last_pc;
	int			*last_champ;
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);
	char		*cycle;

	last_pc = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	last_champ = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	champs = cor->champs;
	first_champ = champs;
	init_op(f);
	while ((champs = first_champ))
	{
		if (cor->opt->n)
		{
			while (champs)
			{
				//Clean process pos
				cur_champ = champs->content;
				if (last_champ[cur_champ->id - 1] && cur_champ->r_cy == 0)
				{
					attron(COLOR_PAIR(2 + last_champ[cur_champ->id - 1]));
					draw_uchar(last_pc[cur_champ->id - 1], \
							(cor->map)[last_pc[cur_champ->id - 1]]);
				}
				champs = champs->next;
			}
			champs = first_champ;
		}
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				if (cur_champ->r_cy == 0)
				{
					if (cor->cycle != 0)
					{
						// Do op
						if (cor->map[cur_champ->pc] > 1 || cor->map[cur_champ->pc] <= 16)
							f[cor->map[cur_champ->pc]](cor, cur_champ);
						else
							f[0](cor, cur_champ);
					}
					// Change r_cy
					if (cor->map[cur_champ->pc] > 1 || cor->map[cur_champ->pc] <= 16)
						cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
					//Print process pos
					if (cor->opt->n)
					{
						attron(COLOR_PAIR(10 + cur_champ->id));
						draw_uchar(cur_champ->pc, (cor->map)[cur_champ->pc]);
						last_pc[cur_champ->id - 1] = cur_champ->pc;
						last_champ[cur_champ->id - 1] = cur_champ->id;
					}
				}
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		//Print cycle
		cycle = ft_itoa((cor->cycle)++);
		attron(COLOR_PAIR(7));
		draw_line(7, 9, cycle);
		free(cycle);
		//Wait event
		getch();
	}
	free(last_pc);
	free(last_champ);
}

int		change_r_cy(t_cor *cor, t_champ *champ)//////////////////////// fonction pour changer r_cy
{
	if (cor->map[champ->pc] <= 0 || cor->map[champ->pc] > 16)
		return (0);
	else
		return (g_op_tab[cor->map[champ->pc] - 1].nb_cycles);
}
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

//The last OPcode function(I don't know where to place it so here, I think is good)

void	ft_aff(t_cor *cor, t_champ  *champ)
{
	int r1;
}

void	ft_move(t_cor *cor, t_champ  *champ)
{
	int r1;
}
