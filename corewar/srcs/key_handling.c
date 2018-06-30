/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:06:17 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/30 19:26:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	draw_state(int state)
{
	if (state)
	{
		draw_line(2, 0, "              ");
		draw_line(2, 0, "** RUNNING **");
	}
	else
	{
		draw_line(2, 0, "             ");
		draw_line(2, 0, "** PAUSED **");
	}
}

static void	apply_timeout(int *timeout, int *ch)
{
	draw_state(1);
	timeout(*timeout / 600);
	*ch = getch();
	timeout(-1);
	if (!ft_strchr("s rewq", *ch))
		*ch = ERR;
	else
		draw_state(0);
}

static void	key_event_noechoed(int *timeout, int *ch)
{
	int		k;

	k = 0;
	if (*ch != ERR)
	{
		draw_state(0);
		if (!ft_strchr("rewq", *ch))
			*ch = getch();
		else
			k = 1;
		while (*ch != 's' && *ch != ERR)
		{
			timeout =  key_handler(timeout, ch);
			if (*ch == ' ' || k == 1)
			{
				k = 0;
				*ch = ERR;
				break ;
			}
			*ch = getch();
		}
		draw_state(1);
	}
	else
		apply_timeout(timeout, ch);
}

void		key_event(int *timeout, int *ch)
{
	noecho();
	key_event_noechoed(timeout, ch);
	echo();
}
