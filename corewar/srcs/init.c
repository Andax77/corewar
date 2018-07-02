/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/02 18:31:37 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		count_champs(t_list *champs)
{
	int		i;

	i = 0;
	while (champs)
	{
		if (((t_champ*)champs->content)->father == 0)
			i++;
		champs = champs->next;
	}
	return (i);
}

int		init_ncurses(t_cor *cor)
{
	t_list	*champs;
	int		i;

	champs = cor->champs;
	i = count_champs(champs);
	if (initscr())
	{
		start_color();
		curs_set(0);
		init_colors(cor->champs);
		init_special_colors();
		attron(COLOR_PAIR(1));
		draw_borders();
		attron(COLOR_PAIR(2));
		draw_map(cor);
		attron(COLOR_PAIR(17));
		draw_infos(cor->champs, 11);
		draw_names(cor->champs);
		print_player(i);
		attron(COLOR_PAIR(3));
		return (1);
	}
	return (0);
}

int		init(char **argv, t_cor *cor)
{
	if (init_cor(cor, argv) == ERROR)
		return (ERROR);
	if (cor->opt->v)
	{
		game_over(cor);
		getch();
		endwin();
	}
	if (cor->opt->a)
		if (cor->aff)
			ft_printf("%s", cor->aff);
	if (cor->winner == 0)
		ft_printf("No Winner\n");
	else if (!cor->opt->d)
		ft_printf("{%s}Contestant %d, \"%s\", has won !\n{eoc}",
				color_player(cor->winner), cor->winner, get_name_champ(cor));
	return (SUCCESS);
}
