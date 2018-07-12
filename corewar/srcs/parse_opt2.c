/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:06:55 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/12 14:57:33 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	err_print(char *str, char *arg)
{
	if (arg)
		ft_printf("{red}'%s' %s{eoc}\n", arg, str);
	else
		ft_printf("{red}%s{eoc}\n", str);
	return (ERROR);
}

int			check_opt(char **argv)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (ft_strequ(argv[i], "-n"))
		{
			if (!argv[i + 1] || !ft_strisdigit(argv[i + 1]) || !argv[i + 2]
					|| !ft_strstr(argv[i + 2], ".cor"))
				return (err_print("Wrong [-n nbr] value", NULL));
			else
				i += 2;
		}
		else if (ft_strequ(argv[i], "-d") || ft_strequ(argv[i], "-dump"))
		{
			if (!argv[i + 1] || !ft_isint(argv[i + 1]) || argv[i + 1][0] == '-')
				return (err_print("Wrong [-d(ump) nbr_cycles] value", NULL));
			else
				++i;
		}
		else if (!ft_strstr(argv[i], ".cor") && !ft_strequ(argv[i], "-a")
				&& !ft_strequ(argv[i], "-v"))
			return (err_print("invalid file <champion.cor>", argv[i]));
	}
	return (SUCCESS);
}

int		check_doubles(t_opt *opt, int index)
{
	int		i;

	i = -1;
	while (++i < index && index < MAX_PLAYERS)
	{
		if (opt->n[i] == opt->n[index])
		{
			ft_printf("{red}n value used twice...\n{eoc}");
			free(opt->n);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int			is_opt(char *str)
{
	int		ret;

	ret = 0;
	(ft_strequ(str, "-a")) ? ret = 1 : 0;
	(ft_strequ(str, "-v")) ? ret = 1 : 0;
	(ft_strequ(str, "-n")) ? ret = 1 : 0;
	(ft_strequ(str, "-d") || ft_strequ(str, "-dump")) ? ret = 1 : 0;
	(ft_strisdigit(str)) ? ret = 1 : 0;
	return (ret);
}

void		print_usage(void)
{
	char	*line;
	int		fd;

	line = NULL;
	if ((fd = open("usage.txt", O_RDONLY)) == -1)
		return ;
	while (fd && get_next_line(fd, &line) == GNL_SUCCESS)
	{
		ft_printf("%s\n", line);
		free(line);
	}
	if (fd)
		close(fd);
}
