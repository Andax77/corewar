/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/07/03 12:58:44 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	init_values(t_cor *cor, char **values)
{
	t_list		*champs;
	int			i;

	i = 0;
	champs = cor->champs;
	while (champs)
	{
		if (((t_champ*)champs->content)->r_cy > -1)
			i++;
		champs = champs->next;
	}
	if (!(values[0] = ft_itoa(cor->cycle)))
		exit(EXIT_FAILURE);
	if (!(values[1] = ft_itoa(i)))
		exit(EXIT_FAILURE);
	if (!(values[2] = ft_itoa(cor->v_cycle)))
		exit(EXIT_FAILURE);
	if (!(values[3] = ft_itoa(cor->cycle_to_die)))
		exit(EXIT_FAILURE);
	if (!(values[4] = ft_itoa(CYCLE_DELTA)))
		exit(EXIT_FAILURE);
	if (!(values[5] = ft_itoa(NBR_LIVE)))
		exit(EXIT_FAILURE);
	if (!(values[6] = ft_itoa(MAX_CHECKS)))
		exit(EXIT_FAILURE);
	values[9] = NULL;
}

static void		print_ctd(char **values)
{
	int		i;

	i = 0;
	draw_line(28, 0, "[--------------------------------------------------]");
	while (i < (50 * ((float)ft_atoi(values[2]) / (float)ft_atoi(values[3]))))
		draw_line(28, 1 + i++, "#");
}

static void		print_values(char **values)
{
	attron(COLOR_PAIR(17));
	draw_line(7, 8, values[0]);
	draw_line(9, 12, "      ");
	draw_line(9, 12, values[1]);
	draw_line(27, 16, "      ");
	draw_line(27, 16, values[2]);
	draw_line(27, 26, "      ");
	draw_line(27, 26, values[3]);
	print_ctd(values);
	draw_line(30, 14, "      ");
	draw_line(30, 14, values[4]);
	draw_line(32, 11, "      ");
	draw_line(32, 11, values[5]);
	draw_line(34, 13, "      ");
	draw_line(34, 13, values[6]);
}

static void		print_champ_values(t_cor *cor, char **values)
{
	t_list	*champs;
	int		id;

	champs = cor->champs;
	while (champs)
	{
		if (!((t_champ*)champs->content)->father)
		{
			id = ((t_champ*)champs->content)->id - 1;
			if (!(values[7] = ft_itoa(((t_champ*)champs->content)->last_live)))
				exit(EXIT_FAILURE);
			if (!(values[8] = ft_itoa(((t_champ*)champs->content)->lives)))
				exit(EXIT_FAILURE);
			draw_line(12 + (4 * id), 32, "       ");
			draw_line(12 + (4 * id), 32, values[7]);
			draw_line(13 + (4 * id), 32, "       ");
			draw_line(13 + (4 * id), 32, values[8]);
			ft_fruit(2, &values[7], &values[8]);
		}
		champs = champs->next;
	}
}

void		print_infos(t_cor *cor)
{
	int			i;
	char		**values;

	i = 0;
	print_cow(cor);
	print_heart(cor);
	values = ft_malloc(10 * sizeof(char*), EXIT_FAILURE);
	init_values(cor, values);
	print_values(values);
	print_champ_values(cor, values);
	while (values[i])
		free(values[i++]);
	free(values);
}
