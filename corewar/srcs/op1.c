/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:05:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/26 22:10:08 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_live(t_cor *cor, t_champ *champ)
{
	int		p;
	int		ori;
	t_list	*tmp;

	tmp = cor->champs;
	ori = champ->pc;
	p = (cor->map[++champ->pc % MEM_SIZE] << 24) + (cor->map[++champ->pc % MEM_SIZE] << 16) +
		(cor->map[++champ->pc % MEM_SIZE] << 8) + cor->map[++champ->pc % MEM_SIZE];
	champ->pc = (champ->pc + 1) % MEM_SIZE;
	if (p == champ->id)
		champ->lives++;
	champ->v_lives++;
	while (tmp)
	{
		if (((t_champ*)tmp->content)->v_id == p && ((t_champ*)tmp->content)->father == 0 && (t_champ*)tmp->content != champ)
		{
//			ft_printf("%s %d\n", ((t_champ*)tmp->content)->name, p);
			((t_champ*)tmp->content)->lives++;
			((t_champ*)tmp->content)->last_live = cor->cycle;
			get_color_heart(1, "Faire un live", ((t_champ*)tmp->content)->id);
			((t_champ*)tmp->content)->live++;
			cor->winner = ((t_champ*)tmp->content)->id;
			((t_champ*)tmp->content)->last_live_pc = champ->pc;
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_ld(t_cor *cor, t_champ *champ)
{
	int		p1;
	int		p2;
	int		ocp;
	int		ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 2);
	p2 = recup_content(cor, champ, ocp, 4, 2);
	if (p2 > 0 && p2 <= REG_NUMBER)
	{
		if (((ocp >> 6) & 3) == DIR_CODE)
			champ->reg[p2 - 1] = p1;
		else
		{
			p1 = ((short)p1 % IDX_MOD) % MEM_SIZE;
			if ((ori + p1) < 0)
				p1 += MEM_SIZE;
			champ->reg[p2 - 1] = (cor->map[(ori + p1) % MEM_SIZE] << 24) +
				(cor->map[(ori + p1 + 1) % MEM_SIZE] << 16) +
				(cor->map[(ori + p1 + 2) % MEM_SIZE] << 8) +
				cor->map[(ori + p1 + 3) % MEM_SIZE];
		}
		if (champ->reg[p2 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_st(t_cor *cor, t_champ *champ)
{
	int		p1;
	short	p2;
	int		ocp;
	int		ori;
	int		i;

	i = -1;
	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 3);
	p2 = recup_content(cor, champ, ocp, 4, 3);
	if (p1 > 0 && p1 <= REG_NUMBER)
	{
		if (((ocp >> 4) & 3) == REG_CODE)
		{
			if (p2 > 0 && p2 <= REG_NUMBER)
				champ->reg[p2 - 1] = champ->reg[p1 - 1];
		}
		else
		{
			p2 = ((short)p2 % IDX_MOD) % MEM_SIZE;
			if ((ori + p2) < 0)
				p2 += MEM_SIZE;
			cor->map[(ori + p2) % MEM_SIZE] = champ->reg[p1 - 1] >> 24;
			cor->map[(ori + p2 + 1) % MEM_SIZE] = champ->reg[p1 - 1] >> 16;
			cor->map[(ori + p2 + 2) % MEM_SIZE] = champ->reg[p1 - 1] >> 8;
			cor->map[(ori + p2 + 3) % MEM_SIZE] = champ->reg[p1 - 1];
			if (cor->opt->v)
			{
				if (champ->last_st)
					while (++i < 4)
					{
						attron(COLOR_PAIR(cor->c_map[champ->last_st_pc + i]));
						draw_uchar(champ->last_st_pc + i, cor->map[champ->last_st_pc + i]);
					}
				attron(COLOR_PAIR(2 + champ->id) | A_BOLD);
				draw_uchar((ori + p2) % MEM_SIZE, champ->reg[p1 - 1] >> 24);
				cor->c_map[(ori + p2) % MEM_SIZE] = champ->id + 2;
				draw_uchar((ori + p2 + 1) % MEM_SIZE, champ->reg[p1 - 1] >> 16);
				cor->c_map[(ori + p2 + 1) % MEM_SIZE] = champ->id + 2;
				draw_uchar((ori + p2 + 2) % MEM_SIZE, champ->reg[p1 - 1] >> 8);
				cor->c_map[(ori + p2 + 2) % MEM_SIZE] = champ->id + 2;
				draw_uchar((ori + p2 + 3) % MEM_SIZE, champ->reg[p1 - 1]);
				cor->c_map[(ori + p2 + 3) % MEM_SIZE] = champ->id + 2;
				attroff(A_BOLD);
				champ->last_st = 1;
				champ->last_st_pc = (ori + p2) % MEM_SIZE;
			}
		}
		if (champ->reg[p1 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_add(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 4);
	p2 = recup_content(cor, champ, ocp, 4, 4);
	p3 = recup_content(cor, champ, ocp, 2, 4);
	if (p1 > 0 && p1 <= REG_NUMBER && p2 > 0 && p2 <= REG_NUMBER && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] + champ->reg[p2 - 1];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}

void	ft_sub(t_cor *cor, t_champ *champ)
{
	int p1;
	int p2;
	int p3;
	int	ocp;
	int	ori;

	ori = champ->pc;
	ocp = cor->map[++champ->pc % MEM_SIZE];
	p1 = recup_content(cor, champ, ocp, 6, 4);
	p2 = recup_content(cor, champ, ocp, 4, 4);
	p3 = recup_content(cor, champ, ocp, 2, 4);
	if (p1 > 0 && p1 <= REG_NUMBER && p2 > 0 && p2 <= REG_NUMBER && p3 > 0 && p3 <= REG_NUMBER)
	{
		champ->reg[p3 - 1] = champ->reg[p1 - 1] - champ->reg[p2 - 1];
		if (champ->reg[p3 - 1] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
	}
	else
		champ->carry = 0;
	champ->pc = (champ->pc + 1) % MEM_SIZE;
}
