/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/21 18:11:23 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_opt	*init_opt(t_opt *opt)
{
	opt = ft_malloc(sizeof(t_opt), ERROR);
	opt->a = 0;
	opt->d = 0;
	opt->s = 0;
	opt->v = 0;
	opt->b = 0;
	opt->bs = 0;
	opt->n = 0;
	opt->ns = 0;
	return (opt);
}

int	check_opt(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-s") ||\
			ft_strequ(av[i], "-v"))
			if (!av[i + 1] || !ft_isdigit(*(av[i + 1])))
				return (ERROR);
		if (ft_strequ(av[i], "--stealth"))
			if (!av[i - 1] || \
			(!ft_strequ(av[i - 1], "-b") && !ft_strequ(av[i - 1], "-n")))
				return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		parse_opt(char **av, t_opt *opt)
{
	if (check_opt(av) == SUCCESS)
	{
		opt = init_opt(opt);
		while (*av)
		{
			(ft_strequ(*av, "-a")) ? opt->a = 1 : 0;
			(ft_strequ(*av, "-d")) ? opt->d = ft_atoi(*++av) : 0;
			(ft_strequ(*av, "-s")) ? opt->s = ft_atoi(*++av) : 0;
			(ft_strequ(*av, "-v")) ? opt->v = ft_atoi(*++av) : 0;
			(ft_strequ(*av, "-b")) ? opt->b = 1 : 0;
			(ft_strequ(*av, "-n")) ? opt->n = 1 : 0;
			if (ft_strequ(*av, "--stealth"))
			{
				if (ft_strequ(*(av - 1), "-b"))
					opt->bs = 1;
				else if (ft_strequ(*(av - 1), "-n"))
					opt->ns = 1;
			}
			av++;
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
}

void	print_usage(void)
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

int		main(int ac, char **av)
{
	t_opt	*opt;

	opt = NULL;
	if (ac == 1)
	{
		print_usage();
		exit(ERROR);
	}
	else if (parse_opt(av, opt) == SUCCESS)
		init(opt);
	else
	{
		print_usage();
		free(opt);
		exit(ERROR);
	}
	free(opt);
	exit(SUCCESS);
}
