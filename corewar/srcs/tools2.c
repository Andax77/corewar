/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:12:06 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/29 12:14:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <corewar.h>

void	order_to_start(t_list **champs)
{
	t_list	*cur;
	t_list	*next;

	cur = *champs;
	*champs = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = *champs;
		*champs = cur;
		cur = next;
	}
}

int		check_live_value(t_cor *cor, int pc)
{
	t_list	*champs;
	int		v_id;

	champs = cor->champs;
	while (champs)
	{
		v_id = ((t_champ*)champs->content)->v_id;
		if (cor->map[pc] == 1 && cor->map[(pc + 4) % MEM_SIZE] + \
(cor->map[(pc + 3) % MEM_SIZE] << 8) + \
(cor->map[(pc + 2) % MEM_SIZE] << 16) + \
(cor->map[(pc + 1) % MEM_SIZE] << 24) == v_id)
			return (((t_champ*)champs->content)->id);
		champs = champs->next;
	}
	return (0);
}

void	dump(t_cor *cor)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	x = 0;
	i = 0;
	j = 0;
	while (y < ft_sqrt(MEM_SIZE))
	{
		(y) ? ft_printf("%#06x :", j) : ft_putstr("0x0000 :");
		while (x < ft_sqrt(MEM_SIZE))
		{
			ft_printf("{%s} %02x{eoc}", color_player(cor->c_map[i] - 2), \
				cor->map[i]);
			x++;
			i++;
		}
		x = 0;
		y++;
		j += ft_sqrt(MEM_SIZE);
		ft_putchar('\n');
	}
}

void	jump(t_cor *cor)
{
	t_list	*champs;
	t_champ	*cur_champ;

	champs = cor->champs;
	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy > -1)
		{
			attron(COLOR_PAIR(20 + cur_champ->id));
			draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
			if (cur_champ->last_live && cur_champ->lives)
			{
				attron(COLOR_PAIR(40 + cur_champ->id));
				draw_uchar(cur_champ->last_live_pc, \
					cor->map[cur_champ->last_live_pc]);
			}
		}
		champs = champs->next;
	}
}
