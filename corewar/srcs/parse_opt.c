/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/19 15:03:34 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	init_opt(t_opt *opt, t_cor *cor)
{
	int		i;

	i = 0;
	opt->a = 0;
	opt->v = 0;
	opt->d = 0;
	opt->n = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	ft_bzero(opt->n, MAX_PLAYERS * sizeof(int));
	cor->opt = opt;
}

static int	check_opt(char **argv)
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
		if (ft_strequ(argv[i], "-dump"))
			if (!argv[i + 1] || !ft_strisdigit(argv[i + 1]))
			{
				ft_printf("{red}Wrong [-dump nbr_cycles] value{eoc}\n");
				return (ERROR);
			}
		i++;
	}
	return (SUCCESS);
}

int			parse_opt(char **argv, t_opt *opt, t_cor *cor)
{
	int				i;
	int				j;
	static int		id;

	i = 0;
	j = -1;
	if (check_opt(argv) == SUCCESS)
	{
		init_opt(opt, cor);
		while (argv[++j])
		{
			(ft_strequ(argv[j], "-a")) ? opt->a = 1 : 0;
			(ft_strequ(argv[j], "-v")) ? opt->v = 1 : 0;
			(ft_strequ(argv[j], "-d") && argv[j + 1]) ? \
				opt->d = ft_atoi(argv[++j]) : 0;
			(ft_strequ(argv[j], "-n") && argv[j + 1]) ? opt->n[i++] = \
				(int)ft_atoi(argv[++j]) : 0;
			(ft_strstr(argv[j], ".cor") && argv[j - 1] && \
				!ft_strisdigit(argv[j - 1]) && j - 2 > 0 && \
				!ft_strequ(argv[j - 2], "-n")) ? opt->n[i++] = ++id : 0;
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int			is_opt(char *str)
{
	int		ret;

	ret = 0;
	(ft_strequ(str, "-a")) ? ret = 1 : 0;
	(ft_strequ(str, "-v")) ? ret = 1 : 0;
	(ft_strequ(str, "-n" )) ? ret = 1 : 0;
	(ft_strequ(str, "-dump")) ? ret = 1 : 0;
	(ft_strisdigit(str)) ? ret = 1 : 0;
	return (ret);
}

void		print_usage(void)
{
	char	*line;
	int		fd;

	line = NULL;
	if (!(fd = open("usage.txt", O_RDONLY)))
		return ;
	while (fd && get_next_line(fd, &line) == GNL_SUCCESS)
	{
		ft_printf("%s\n", line);
		free(line);
	}
	if (fd)
		close(fd);
}
