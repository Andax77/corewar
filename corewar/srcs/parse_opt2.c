/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/03 16:17:45 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		init_opt(t_opt *opt, t_cor *cor)
{
	opt->a = 0;
	opt->v = 0;
	opt->d = 0;
	opt->n = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	ft_bzero(opt->n, MAX_PLAYERS * sizeof(int));
	cor->opt = opt;
}

int		check_opt(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-n"))
			if (!argv[i + 1] || !ft_strisdigit(argv[i + 1]) || !argv[i + 2] || \
					!ft_strstr(argv[i + 2], ".cor"))
			{
				ft_printf("{red}Wrong [-n nbr] value{eoc}\n");
				return (ERROR);
			}
		if (ft_strequ(argv[i], "-d") || ft_strequ(argv[i], "-dump"))
			if (!argv[i + 1] || !ft_strisdigit(argv[i + 1]))
			{
				ft_printf("{red}Wrong [-d nbr_cycles] value{eoc}\n");
				return (ERROR);
			}
		i++;
	}
	return (SUCCESS);
}

void	verif_doublons(t_opt *opt, int index)
{
	int		i;

	i = -1;
	while (++i < index)
	{
		if (opt->n[i] == opt->n[index])
		{
			opt->n[index] += 1;
			verif_doublons(opt, index);
			break ;
		}
	}
}

int		is_opt(char *str)
{
	int		ret;

	ret = 0;
	(ft_strequ(str, "-a")) ? ret = 1 : 0;
	(ft_strequ(str, "-v")) ? ret = 1 : 0;
	(ft_strequ(str, "-n" )) ? ret = 1 : 0;
	(ft_strequ(str, "-d") || ft_strequ(str, "-dump")) ? ret = 1 : 0;
	(ft_strisdigit(str)) ? ret = 1 : 0;
	return (ret);
}

int		print_usage(void)
{
	char	*line;
	int		fd;

	line = NULL;
	if (!(fd = open("usage.txt", O_RDONLY)))
		return (0);
	while (fd && get_next_line(fd, &line) == GNL_SUCCESS)
	{
		ft_printf("%s\n", line);
		free(line);
	}
	if (fd)
		close(fd);
	return (1);
}
