/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/22 23:53:27 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		init_ncurse(WINDOW *border1, WINDOW *border2, WINDOW *border3)
{
	wchar_t	c;

	c = (wchar_t)"\u25A0";
	initscr();
	border1 = subwin(stdscr, 40, 80, 0, 0);
	wborder(border1, c, c, c, c, c, c, c, c);
	border2 = subwin(stdscr, 40, 40, 0, 80);
	wborder(border2, c, c, c, c, c, c, c, c);
	border3 = subwin(stdscr, 10, 120, 39, 0);
	wborder(border3, c, c, c, c, c, c, c, c);
	refresh();
	getch();
	endwin();
	return (SUCCESS);
}

int		init(t_opt *opt)
{
	WINDOW	*border1;
	WINDOW	*border2;
	WINDOW	*border3;

	border1 = NULL;
	border2 = NULL;
	border3 = NULL;
	if (opt->n)
		if (!init_ncurse(border1, border2, border3))
		{
			free(border1);
			free(border2);
			free(border3);
			return (ERROR);
		}
	free(border1);
	free(border2);
	free(border3);
	return (SUCCESS);
}
