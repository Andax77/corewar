/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/16 16:37:43 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			init_opt(t_opt *opt, t_cor *cor)
{
	int		max_players;

	max_players = MAX_PLAYERS;
	opt->a = 0;
	opt->v = 0;
	opt->d = 0;
	opt->n = (int*)ft_malloc((max_players + 1) * sizeof(int), EXIT_FAILURE);
	cor->opt = opt;
}

static int		get_values(char **argv, int j, int i, t_opt *opt)
{
	(ft_strequ(argv[j], "-a")) ? opt->a = 1 : 0;
	(ft_strequ(argv[j], "-v")) ? opt->v = 1 : 0;
	((ft_strequ(argv[j], "-d") || ft_strequ(argv[j], "-dump")) && argv[j + 1])
		? opt->d = ft_atoi(argv[j + 1]) : 0;
	if (ft_strequ(argv[j], "-n") && argv[j + 1])
	{
		opt->n[i] = ft_atoi(argv[++j]);
		opt->n_ed = 1;
		check_doubles(opt, ++i);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int				parse_opt(char **argv, t_opt *opt, t_cor *cor)
{
	int		i;
	int		j;
	int		id;

	i = 0;
	j = 0;
	id = 0;
	if (check_opt(argv) == SUCCESS)
	{
		init_opt(opt, cor);
		while (argv[++j])
			if (!ft_strstr(argv[j], ".cor"))
				get_values(argv, j, i, opt);
			else
			{
				if (!opt->n_ed && i <= MAX_PLAYERS)
					opt->n[i] = ++id;
				else
					opt->n_ed = 0;
				check_doubles(opt, ++i - 1);
			}
		return (SUCCESS);
	}
	return (ERROR);
}
