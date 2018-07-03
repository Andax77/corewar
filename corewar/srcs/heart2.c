/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:00:49 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/03 16:11:48 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		heart_color(void)
{
	init_pair(26, COLOR_RED, COLOR_RED);
	init_pair(27, COLOR_GREEN, COLOR_GREEN);
	init_pair(28, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(29, COLOR_BLUE, COLOR_BLUE);
	init_pair(30, 17, 17);
}

int			stat_heart(t_list *champs, int lives, int nb)
{
	int		stat;
	int		champs_lives;

	stat = 3;
	champs_lives = ((t_champ*)champs->content)->lives;
	if (lives == 0 || champs_lives > lives / nb)
		stat = 1;
	else if (lives)
		stat = 2;
	return (stat);
}

void		print_heart(t_cor *cor)
{
	t_list	*champs;
	int		stat;
	int		lives;
	int		nb;

	nb = 0;
	lives = 0;
	champs = cor->champs;
	while (champs)
	{
		if (((t_champ*)champs->content)->father == 0 && ++nb)
			lives += ((t_champ*)champs->content)->lives;
		champs = champs->next;
	}
	champs = cor->champs;
	while (champs)
	{
		if (((t_champ*)champs->content)->father == 0)
		{
			stat = stat_heart(champs, lives, nb);
			print_heart2(((t_champ *)champs->content)->id, stat);
		}
		champs = champs->next;
	}
}
