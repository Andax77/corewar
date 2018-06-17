/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/17 12:19:07 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	clean(t_cor *cor, t_list *champs, int *last_champ, int *last_pc)
{
	t_champ *cur_champ;

	while (champs)
	{
		cur_champ = champs->content;
		if (last_champ[cur_champ->id - 1] && cur_champ->r_cy == 0)
		{
			if (cor->map[last_pc[cur_champ->id - 1]] != 1)
			{
				attron(COLOR_PAIR(2 + last_champ[cur_champ->id - 1]));
				draw_uchar(last_pc[cur_champ->id - 1], \
					(cor->map)[last_pc[cur_champ->id - 1]]);
			}
			if (cor->map[cur_champ->pc] == 1 && cur_champ->lives > 0)
			{
				attron(COLOR_PAIR(2 + last_champ[cur_champ->id - 1]));
				draw_uchar(cur_champ->last_live_pc, \
					(cor->map)[last_pc[cur_champ->id - 1]]);
			}
		}
		champs = champs->next;
	}
}

void	cycle_job(t_cor *cor, t_champ *cur_champ, int *last_champ, int *last_pc)
{
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);

	init_op(f);
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
	// Print process pos
	if (cor->opt->n)
	{
		if (cor->map[cur_champ->pc] == 1)
		{
			attron(COLOR_PAIR(20 + cur_champ->id));
			draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
		}
		else
		{
			attron(COLOR_PAIR(10 + cur_champ->id));
			draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
		}
		last_pc[cur_champ->id - 1] = cur_champ->pc;
		last_champ[cur_champ->id - 1] = cur_champ->id;
	}
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
				attron(COLOR_PAIR(7));
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
				attron(COLOR_PAIR(7));
				draw_line(4, 22, "    ");
				draw_line(4, 22, p_p_c);
				free(p_p_c);
			}
			else if (*ch == 'w' && *timeout < 950)
			{
				p_p_c = ft_itoa(1000 - ++*timeout);
				attron(COLOR_PAIR(7));
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
				attron(COLOR_PAIR(7));
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
	char	*cycle;
	char	*processes;
	t_list	*champs;
	char	*last_live;
	char	*lives;
	int		i;

	i = 0;
	champs = cor->champs;
	cycle = ft_itoa((cor->cycle)++);
	processes = ft_itoa(ft_lstcount(cor->champs));
	attron(COLOR_PAIR(7));
	draw_line(7, 9, cycle);
	draw_line(9, 12, "    ");
	draw_line(9, 12, processes);
	if (cor->cycle == 1)
	{
		attron(COLOR_PAIR(7));
		draw_line(4, 22, "50");
	}
	while (champs)
	{
		last_live = ft_itoa(((t_champ*)champs->content)->last_live);
		lives = ft_itoa(((t_champ*)champs->content)->lives);
		draw_line(12 + (4 * i), 32, "    ");
		draw_line(12 + (4 * i), 32, last_live);
		draw_line(13 + (4 * i), 32, "    ");
		draw_line(13 + (4 * i), 32, lives);
		i++;
		champs = champs->next;
		free(last_live);
		free(lives);
	}
	free(cycle);
	free(processes);
}

void	cycle(t_cor *cor)
{
	t_list		*champs;
	t_list		*first_champ;
	t_champ		*cur_champ;
	int			*last_pc;
	int			*last_champ;
	int			timeout;
	int			ch;

	timeout = 950;
	last_pc = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	last_champ = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	first_champ = cor->champs;
	while ((champs = first_champ))
	{
		// Clean cursor
		if (cor->opt->n)
			clean(cor, champs, last_champ, last_pc);
		while (champs)
		{
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				// Do op or decrement r_cy
				if (cur_champ->r_cy == 0)
					cycle_job(cor, cur_champ, last_champ, last_pc);
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
		}
		// Print infos
		if (cor->opt->n)
			print_infos(cor);
		// Key event
		if (cor->opt->n)
			key_event(&timeout, &ch);
	}
	free(last_pc);
	free(last_champ);
}
