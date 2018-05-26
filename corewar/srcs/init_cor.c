/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/26 02:06:48 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static uint64_t swap_u_int(uint64_t c)
{
	c = ((c << 8) & 0xFF00FF00) | ((c >> 8) & 0xFF00FF);
	return ((c << 16) | ((c >> 16) & 0xFFFF));
}

static void		populate_instru(t_champ **champ, uint64_t c)
{
	t_list		**instru;
	char		*tmp;
	t_list		*new;

	instru = &(*champ)->instru;
	if (!(tmp = ft_itoa(swap_u_int(c))))
		exit(EXIT_FAILURE);
	if (!*instru)
	{
		if (!(*instru = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			exit(EXIT_FAILURE);
		ft_lstaddend(instru, new);
	}//ft_printf("%s\n", tmp);
	free(tmp);
}

static int		get_champ(t_champ **champ, char *path)
{
	uint64_t	c;
	int			fd;
	int			ret;

	if (path)
	{
		fd = open(path, O_RDONLY);
		while ((ret = read(fd, &c, 8)))
			populate_instru(champ, c);
		close(fd);
		if (ret == -1)
			return (ERROR);
	}
	if (check_champ(champ, path) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int		populate_champs(t_list **champs, char *path)
{
	t_list		*new;
	t_champ		*champ;

	champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (get_champ(&champ, path) == ERROR)
		return (ERROR);
	if (!*(champs))
	{
		if (!(*champs = ft_lstnew(champ, sizeof(t_champ))))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(champ, sizeof(t_champ))))
			exit(EXIT_FAILURE);
		ft_lstaddend(champs, new);
	}
	free(champ);
	return (SUCCESS);
}

int	init_cor(t_cor *cor, char **argv)
{
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (++argv && *argv)
	{
		if (ft_strstr(*argv, ".cor") && ++n && n <= MAX_PLAYERS)
		{
			if (populate_champs(&cor->champs, *argv) == ERROR)
				return (ERROR);
		}
		else if (!is_opt(*argv))
		{
			print_usage();
			return (ERROR);
		}
	}
	if (!(cor->map = ft_strnew(MEM_SIZE)))
		exit(EXIT_FAILURE);
	if (cor->opt->n && !init_ncurses(cor->opt))
		return (ERROR);
	//TODO GOGO Algo
	return (SUCCESS);
}
