/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/29 13:01:51 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		get_values(char **argv, int j, int i, t_opt *opt)
{
	(ft_strequ(argv[j], "-a")) ? opt->a = 1 : 0;
	(ft_strequ(argv[j], "-v")) ? opt->v = 1 : 0;
	(ft_strequ(argv[j], "-d") && argv[j + 1]) ? \
		opt->d = ft_atoi(argv[j + 1]) : 0;
	if (ft_strequ(argv[j + 1], "-n"))
	{
		opt->n[i] = ft_atoi(argv[++j]);
		verif_doublons(opt, ++i - 1);
		++j;
	}
}

int			parse_opt(char **argv, t_opt *opt, t_cor *cor)
{
	int				i;
	int				j;
	int				id;

	i = 0;
	j = 0;
	id = 0;
	if (check_opt(argv) == SUCCESS)
	{
		init_opt(opt, cor);
		while (argv[++j])
		{
			if (!ft_strstr(argv[j], ".cor"))
				get_values(argv, j, i, opt);
			else
			{
				opt->n[i] = ++id;
				verif_doublons(opt, ++i - 1);
			}
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
}
