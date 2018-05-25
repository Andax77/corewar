/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/25 13:39:16 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	init_opt(t_opt *opt, t_cor *cor)
{
	opt->a = 0;
	opt->d = 0;
	opt->s = 0;
	opt->v = 0;
	opt->b = 0;
	opt->bs = 0;
	opt->n = 0;
	opt->ns = 0;
	cor->opt = opt;
}

int	check_opt(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-d") || ft_strequ(argv[i], "-s") ||\
			ft_strequ(argv[i], "-v"))
			if (!argv[i + 1] || !ft_isdigit(*(argv[i + 1])))
				return (ERROR);
		if (ft_strequ(argv[i], "--stealth"))
			if (!argv[i - 1] || \
			(!ft_strequ(argv[i - 1], "-b") && !ft_strequ(argv[i - 1], "-n")))
				return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		parse_opt(char **argv, t_opt *opt, t_cor *cor)
{
	if (check_opt(argv) == SUCCESS)
	{
		init_opt(opt, cor);
		while (*argv)
		{
			(ft_strequ(*argv, "-a")) ? (opt)->a = 1 : 0;
			(ft_strequ(*argv, "-d")) ? (opt)->d = ft_atoi(*++argv) : 0;
			(ft_strequ(*argv, "-s")) ? (opt)->s = ft_atoi(*++argv) : 0;
			(ft_strequ(*argv, "-v")) ? (opt)->v = ft_atoi(*++argv) : 0;
			(ft_strequ(*argv, "-b")) ? (opt)->b = 1 : 0;
			(ft_strequ(*argv, "-n")) ? (opt)->n = 1 : 0;
			if (ft_strequ(*argv, "--stealth"))
			{
				if (ft_strequ(*(argv - 1), "-b"))
					opt->bs = 1;
				else if (ft_strequ(*(argv - 1), "-n"))
					opt->ns = 1;
			}
			argv++;
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

void	free_cor(t_cor *cor)
{
	free(cor->opt);
	free(cor->champs);
	free(cor->map);
	free(cor);
}

int		main(int argc, char **argv)
{
	t_opt	*opt;
	t_cor	*cor;

	opt = ft_malloc(sizeof(t_opt), EXIT_FAILURE);
	cor = ft_malloc(sizeof(t_cor), EXIT_FAILURE);
	if (argc == 1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	else if (parse_opt(argv, opt, cor) == SUCCESS)
		init(argv, cor);
	else
	{
		print_usage();
		free_cor(cor);
		exit(EXIT_FAILURE);
	}
	free_cor(cor);
	exit(EXIT_SUCCESS);
}
