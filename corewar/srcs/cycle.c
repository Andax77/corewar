/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/24 19:44:20 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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

void	clean(t_cor *cor, t_list *champs)
{
	t_champ		*cur_champ;
	int			v_id;

	while (champs)
	{
		cur_champ = champs->content;
		if (cur_champ->r_cy == 0)
		{
			if ((v_id = check_live_value(cor, cur_champ->last_pc)))
			{
				attron(COLOR_PAIR(40 + v_id));
				draw_uchar(cur_champ->last_pc, cor->map[cur_champ->last_pc]);
				if (cur_champ->lives > 0 && cur_champ->last_pc != cur_champ->last_live_pc)
				{
					attron(COLOR_PAIR(2 + cur_champ->id));
					draw_uchar(cur_champ->last_live_pc, cor->map[cur_champ->last_live_pc]);
				}
			}
			else
			{
				attron(COLOR_PAIR(2 + cur_champ->id));
				draw_uchar(cur_champ->last_pc, cor->map[cur_champ->last_pc]);
			}
		}
		champs = champs->next;
	}
}

void	cycle_job(t_cor *cor, t_champ *cur_champ)
{
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);

	init_op(f);
	if (cor->cycle != 0)
	{
		// Do op
		if (cor->map[cur_champ->pc] >= 1 && cor->map[cur_champ->pc] <= 16)
			f[cor->map[cur_champ->pc]](cor, cur_champ);
		else
			f[0](cor, cur_champ);
	}
	// Change r_cy
	if (cor->map[cur_champ->pc] >= 1 && cor->map[cur_champ->pc] <= 16)
		cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
	// Print process pos
	if (cor->opt->v)
	{
		attron(COLOR_PAIR(20 + cur_champ->id));
		draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
	}
	cur_champ->last_pc = cur_champ->pc;
}

void	key_event(int *timeout, int *ch)
{
	char	*p_p_c;
	int		k;

	k = 0;
	if (*ch != ERR)
	{
		noecho();
		draw_line(2, 0, "             ");
		draw_line(2, 0, "** PAUSED **");
		if (!ft_strchr("rewq", *ch))
			*ch = getch();
		else
			k = 1;
		while (*ch != 's' && *ch != ERR)
		{
			if (*ch == 'e' && *timeout > 0)
			{
				p_p_c = ft_itoa(1000 - --*timeout);
				attron(COLOR_PAIR(17));
				draw_line(4, 22, "    ");
				draw_line(4, 22, p_p_c);
				free(p_p_c);
			}
			else if (*ch == 'r' && *timeout > 1)
			{
				if (1000 - (*timeout - 10) > 1000)
					p_p_c = ft_itoa(1000 - (*timeout = 0));
				else
					p_p_c = ft_itoa(1000 - (*timeout -= 10));
				attron(COLOR_PAIR(17));
				draw_line(4, 22, "    ");
				draw_line(4, 22, p_p_c);
				free(p_p_c);
			}
			else if (*ch == 'w' && *timeout < 950)
			{
				p_p_c = ft_itoa(1000 - ++*timeout);
				attron(COLOR_PAIR(17));
				draw_line(4, 22, "    ");
				draw_line(4, 22, p_p_c);
				free(p_p_c);
			}
			else if (*ch == 'q' && *timeout < 950)
			{
				if (1000 - (*timeout + 10) < 50)
					p_p_c = ft_itoa(1000 - (*timeout = 950));
				else
					p_p_c = ft_itoa(1000 - (*timeout += 10));
				attron(COLOR_PAIR(17));
				draw_line(4, 22, "    ");
				draw_line(4, 22, p_p_c);
				free(p_p_c);
			}
			if (*ch == ' ' || k == 1)
			{
				k = 0;
				*ch = ERR;
				break ;
			}
			*ch = getch();
		}
		draw_line(2, 0, "              ");
		draw_line(2, 0, "** RUNNING **");
		echo();
	}
	else
	{
		noecho();
		draw_line(2, 0, "              ");
		draw_line(2, 0, "** RUNNING **");
		timeout(*timeout / 50);
		*ch = getch();
		timeout(-1);
		if (!ft_strchr("s rewq", *ch))
			*ch = ERR;
		else
		{
			draw_line(2, 0, "             ");
			draw_line(2, 0, "** PAUSED **");
		}
		echo();
	}
}

void	print_infos(t_cor *cor)
{
	t_list		*champs;
	char		*cycle;
	char		*processes;
	char		*last_live;
	char		*lives;
	char		*cycle_to_die;
	char		*cycle_delta;
	char		*nbr_live;
	char		*max_checks;
	int			i;
	int			id;


	i = 0;
	id = 0;
	print_cow(cor);
	print_heart(cor);
	champs = cor->champs;
	cycle = ft_itoa((cor->cycle));
	//ft_printf("id = %d\n", ((t_champ*)champs->content)->id);
	while (champs)
	{
		//ft_printf("r_cy = %d\n", ((t_champ*)champs->content)->id);
		if (((t_champ*)champs->content)->r_cy > -1)
			i++;
		champs = champs->next;
	}
	champs = cor->champs;
	processes = ft_itoa(i);
	cycle_to_die = ft_itoa(cor->cycle_to_die);
	cycle_delta = ft_itoa(CYCLE_DELTA);
	nbr_live = ft_itoa(NBR_LIVE);
	max_checks = ft_itoa(MAX_CHECKS);
	attron(COLOR_PAIR(17));
	draw_line(7, 8, cycle);
	draw_line(9, 12, "    ");
	draw_line(9, 12, processes);
	draw_line(27, 16, "    ");
	draw_line(27, 16, cycle_to_die);
	draw_line(29, 14, "    ");
	draw_line(29, 14, cycle_delta);
	draw_line(31, 11, "    ");
	draw_line(31, 11, nbr_live);
	draw_line(33, 13, "    ");
	draw_line(33, 13, max_checks);
	if (cor->cycle == 1)
	{
		attron(COLOR_PAIR(17));
		draw_line(4, 22, "50");
	}
	while (champs)
	{
		if (!((t_champ*)champs->content)->father)
		{
			ft_printf("-> %d ", ((t_champ*)champs->content)->op_nb % 4);
			for (int j = 0; j < ((t_champ*)champs->content)->op_nb; j++)
			{
				ft_printf("%x", ((t_champ*)champs->content)->splited_prog[j]);
			}
			id = ((t_champ*)champs->content)->id - 1;
			last_live = ft_itoa(((t_champ*)champs->content)->last_live);
			lives = ft_itoa(((t_champ*)champs->content)->lives);
			draw_line(12 + (4 * id), 32, "    ");
			draw_line(12 + (4 * id), 32, last_live);
			draw_line(13 + (4 * id), 32, "    ");
			draw_line(13 + (4 * id), 32, lives);
			free(last_live);
			free(lives);
		}
		champs = champs->next;
	}
	free(cycle);
	free(processes);
	free(cycle_to_die);
	free(cycle_delta);
	free(nbr_live);
	free(max_checks);
}

int		check_lives(t_cor *cor)
{
	t_list	*champs;
	int		nbr_live;

	nbr_live = 0;
	champs = cor->champs;
	while (champs)
	{
		nbr_live += ((t_champ*)champs->content)->lives;
		((t_champ*)champs->content)->lives = 0;
		champs = champs->next;
	}
	if (nbr_live >= NBR_LIVE || cor->checks == MAX_CHECKS)
	{
		cor->cycle_to_die -= CYCLE_DELTA;
		if (cor->checks == MAX_CHECKS)
			cor->checks = 0;
	}
	else
		cor->checks++;
	if (cor->cycle_to_die <= 0)
	{
		cor->cycle_to_die = 0;
		return (0);
	}
	return (1);
}

void	cycle(t_cor *cor)
{
	t_list		*champs;
	t_champ		*cur_champ;
	int			timeout;
	int			ch;
	int			ret;

	ch = ' ';
	ret = 1;
	timeout = 950;
	while ((champs = cor->champs))
	{
		// Clean cursor
		if (cor->opt->v)
			clean(cor, champs);
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				// Do op or decrement r_cy
				if (cur_champ->r_cy == 0)
					cycle_job(cor, cur_champ);
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		// Check champs lives
		if (cor->cycle % cor->cycle_to_die == 0 && cor->cycle > 0)
			ret = check_lives(cor);
		// Print infos
		if (cor->opt->v)
			print_infos(cor);
		// Key event
		if (cor->opt->v)
			key_event(&timeout, &ch);
		// Check end
		if (!ret)
			break ;
		else
			cor->cycle++;
	}
}
