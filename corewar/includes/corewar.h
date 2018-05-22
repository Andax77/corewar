/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:01:48 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/22 22:02:15 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ncurses.h>

enum			e_list
{
	FINISHED, UNFINISHED, ERROR, SUCCESS
};

typedef struct	s_opt
{
	int			a;
	int			d;
	int			s;
	int			v;
	int			b;
	int			bs;
	int			n;
	int			ns;
}				t_opt;

int		init(t_opt *opt);
