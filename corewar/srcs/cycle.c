/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/20 04:02:16 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	clean(t_cor *cor, t_list *champs, t_list *champs_h)
{
	t_champ		*cur_champ;
	t_histo		*last_champ;

	while (champs && champs_h)
	{
		cur_champ = champs->content;
		last_champ = champs_h->content;
		if (last_champ->id && cur_champ->r_cy == 0)
		{
			if (cor->map[last_champ->pc] != 1 || \
			cor->map[(cur_champ->pc + 4) % MEM_SIZE] + \
			(cor->map[(cur_champ->pc + 3) % MEM_SIZE] << 8) + \
			(cor->map[(cur_champ->pc + 2) % MEM_SIZE] << 16) + \
			(cor->map[(cur_champ->pc + 1) % MEM_SIZE] << 24) != cur_champ->v_id)
			{
				attron(COLOR_PAIR(2 + last_champ->id));
				draw_uchar(last_champ->pc, cor->map[last_champ->pc]);
			}
			else if (cur_champ->lives > 0 && \
					last_champ->pc != cur_champ->last_live_pc)
			{
				attron(COLOR_PAIR(2 + last_champ->id));
				draw_uchar(cur_champ->last_live_pc, \
					cor->map[cur_champ->last_live_pc]);
			}
		}
		champs_h = champs_h->next;
		champs = champs->next;
	}
}

void	cycle_job(t_cor *cor, t_champ *cur_champ, t_histo *last_champ, t_list *champs_h)
{
	void		(*f[17])(t_cor *cor, t_champ *cur_champ);
	t_histo		*last;
	t_list		*new_h;
	t_list		*first_champ;
	int			i;

	i = 0;
	init_op(f);
	if (cor->cycle != 0)
	{
		// Do op
		if (cor->map[cur_champ->pc] >= 1 && cor->map[cur_champ->pc] <= 16)
		{
			if (cor->map[cur_champ->pc] == 12 || cor->map[cur_champ->pc] == 15)
			{
				last = ft_malloc(sizeof(t_histo), EXIT_FAILURE);
				new_h = ft_lstnew(last, sizeof(t_histo*));
				first_champ = champs_h;
				while (first_champ)
				{
					i++;
					if (((t_champ*)first_champ->content)->id == cur_champ->id \
					&& ((t_champ*)first_champ->next->content)->id != cur_champ->id)
						break ;
					first_champ = first_champ->next;
				}
				ft_lstinsert(&champs_h, new_h, i);
				free(last);
			}
			f[cor->map[cur_champ->pc]](cor, cur_champ);
		}
		else
			f[0](cor, cur_champ);
	}
	// Change r_cy
	if (cor->map[cur_champ->pc] >= 1 && cor->map[cur_champ->pc] <= 16)
		cur_champ->r_cy = change_r_cy(cor, cur_champ) - 1;
	// Print process pos
	if (cor->opt->v)
	{
		if (cor->map[cur_champ->pc] == 1 && \
		cor->map[(cur_champ->pc + 4) % MEM_SIZE] + \
		(cor->map[(cur_champ->pc + 3) % MEM_SIZE] << 8) + \
		(cor->map[(cur_champ->pc + 2) % MEM_SIZE] << 16) + \
		(cor->map[(cur_champ->pc + 1) % MEM_SIZE] << 24) == cur_champ->v_id)
		{
			attron(COLOR_PAIR(40 + cur_champ->id));
			draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
			stat_heart(cor, cor->champs, 10);
			cur_champ->live++;
		}
		else
		{
			attron(COLOR_PAIR(20 + cur_champ->id));
			draw_uchar(cur_champ->pc, cor->map[cur_champ->pc]);
		}
		last_champ->pc = cur_champ->pc;
		last_champ->id = cur_champ->id;
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
	static int	j;

	champs = cor->champs;
	if (cor->cycle == 0)
		j = ft_lstcount(champs);
	i = 0;
	print_cow(cor);
	print_heart(cor);
	cycle = ft_itoa((cor->cycle));
	while (champs)
	{
		if (((t_champ*)champs->content)->r_cy >= 0)
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
	i = 0;
	while (champs && i < j)
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
		if (((t_champ*)champs->content)->lives == 0)
			((t_champ*)champs->content)->r_cy = -1;
		else
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
	t_list		*first_champ;
	t_champ		*cur_champ;
	t_list		*champs_h;
	t_list		*new_h;
	t_list		*first_champ_h;
	t_histo		*last_champ;
	int			timeout;
	int			ch;
	int			ret;

	ret = 1;
	timeout = 950;
	first_champ = cor->champs;
	champs_h = NULL;
	// Init historic
	while (first_champ)
	{
		if (!champs_h)
		{
			last_champ = ft_malloc(sizeof(t_histo), EXIT_FAILURE);
			champs_h = ft_lstnew(last_champ, sizeof(t_histo*));
		}
		else
		{
			last_champ = ft_malloc(sizeof(t_histo), EXIT_FAILURE);
			new_h = ft_lstnew(last_champ, sizeof(t_histo*));
			ft_lstaddend(&champs_h, new_h);
		}
		free(last_champ);
		first_champ = first_champ->next;
	}
	first_champ = cor->champs;
	first_champ_h = champs_h;
	while ((champs = first_champ) && (champs_h = first_champ_h))
	{
		// Clean cursor
		if (cor->opt->v)
			clean(cor, champs, champs_h);
		while (champs && champs_h)
		{
			last_champ = champs_h->content;
			cur_champ = champs->content;
			if (cur_champ->r_cy > -1)
			{
				// Do op or decrement r_cy
				if (cur_champ->r_cy == 0)
					cycle_job(cor, cur_champ, last_champ, champs_h);
				else
					cur_champ->r_cy--;
			}
			champs = champs->next;
			champs_h = champs_h->next;
		}
		// Check champs lives
		if (cor->cycle % cor->cycle_to_die == 0 && cor->cycle > 0)
			ret = check_lives(cor);
		// Print infos
		if (cor->opt->v)
			print_infos(cor);
		if (!ret)
			break ;
		else
			cor->cycle++;
		// Key event
		if (cor->opt->v)
			key_event(&timeout, &ch);
	}
	champs_h = first_champ_h;
	ft_lstdel(&champs_h, del);
}
