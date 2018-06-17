/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/17 20:05:45 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	init_opt(t_opt *opt, t_cor *cor)
{
	opt->a = 0;
	opt->v = 0;
	opt->d = 0;
	opt->n = (int*)ft_malloc(MAX_PLAYERS * sizeof(int), EXIT_FAILURE);
	cor->opt = opt;
}

static int	check_opt(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-n"))
			if (!argv[i + 1] || !ft_isdigit(*(argv[i + 1])) ||\
				ft_atoi(argv[i + 1]) > MAX_PLAYERS)
			{
				ft_printf("{red}Wrong [-n nbr] value{eoc}\n");
				return (ERROR);
			}
		if (ft_strequ(argv[i], "-dump"))
			if (!argv[i + 1] || !ft_isdigit(*(argv[i + 1])))
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
	int		i;

	i = 0;
	if (check_opt(argv) == SUCCESS)
	{
		init_opt(opt, cor);
		while (*argv)
		{
			(ft_strequ(*argv, "-a")) ? (opt)->a = 1 : 0;
			(ft_strequ(*argv, "-v")) ? (opt)->v = 1 : 0;
			(ft_strequ(*argv, "-d")) ? (opt)->d = ft_atoi(*++argv): 0;
			(ft_strequ(*argv, "-n")) ? (opt)->n[i] = ft_atoi(*++argv): 0;
			argv++;
			i++;
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
	(ft_strequ(str, "-n")) ? ret = 1 : 0;
	(ft_strequ(str, "-dump")) ? ret = 1 : 0;
	(ft_isdigit(str[0]) && ft_is_int(str)) ? ret = 1 : 0;
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
