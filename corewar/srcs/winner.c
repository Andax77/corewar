/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/11 10:47:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		print_intro(t_cor *cor)
{
	t_list	*champ;
	t_champ	*tmp;

	tmp = NULL;
	if ((champ = cor->champs))
		ft_printf("Introducing contestants...\n");
	while (champ)
	{
		if (((t_champ*)champ->content)->father == 0)
			ft_printf("{%s}* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\
\n{eoc}", color_player(((t_champ*)champ->content)->id),\
		((t_champ*)champ->content)->v_id, ((t_champ*)champ->content)->op_nb,\
		((t_champ*)champ->content)->name, ((t_champ*)champ->content)->comment);
		champ = champ->next;
	}
	//ft_putchar('\n');
}

char		*color_player(int id)
{
	if (id == 1)
		return ("red");
	else if (id == 2)
		return ("green");
	else if (id == 3)
		return ("yellow");
	else if (id == 4)
		return ("blue");
	return ("eoc");
}

char		*get_name_champ(t_cor *cor)
{
	t_list	*champ;

	champ = cor->champs;
	while (champ)
	{
		if (((t_champ*)champ->content)->id == cor->winner && \
((t_champ*)champ->content)->father == 0)
			return (((t_champ*)champ->content)->name);
		champ = champ->next;
	}
	return (NULL);
}

void		game_over(t_cor* cor)
{
	char	*winner;
	int		id;
	int		nb;

	nb = 56;
	id = cor->winner;
	winner = get_name_champ(cor);
	if (!winner)
		winner = "No One..";
	draw_line(36, 0, "WINNER IS : ");
	attron(COLOR_PAIR(id + 2));
	draw_line(36, 12, winner);
	draw_line(nb++, 50, "  ");
	draw_line(nb++, 0, "                                                    ");
	draw_line(nb++, 0, "  ****  ***  *   * *****    ***  ** ** ***** *****  ");
	draw_line(nb++, 0, " ***** ***** ** ** **      ***** ** ** **    ** **  ");
	draw_line(nb++, 0, " **    ** ** ***** ***     ** ** ***** ***   ** **  ");
	draw_line(nb++, 0, " ** ** ***** ***** **      ** ** ***** **    *****  ");
	draw_line(nb++, 0, " ***** ** ** ** ** *****   *****  ***  ***** ** **  ");
	draw_line(nb++, 0, "  ***  ** ** ** ** *****    ***    *   ***** **  *  ");
	draw_line(nb++, 0, "                                                    ");
}
