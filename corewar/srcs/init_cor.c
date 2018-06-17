/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/17 19:46:52 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		init_memory(t_cor *cor)
{
	t_list			*champs;
	unsigned char	*tmp_prog;
	int				i;
	int				j;
	int				nb_champs;

	i = 0;
	j = 0;
	champs = cor->champs;
	nb_champs = ft_lstcount(champs);
	while (champs)
	{
		((t_champ*)champs->content)->pc = i;
		tmp_prog = ((t_champ *)champs->content)->splited_prog;
		while (j < ((t_champ *)champs->content)->op_nb)
		{
			cor->map[i + j] = tmp_prog[j];
			j++;
		}
		j = 0;
		i += MEM_SIZE / nb_champs;
		champs = champs->next;
	}
}

static void		populate_instru(t_champ **champ, int64_t c)
{
	t_list		**instru;
	char		*tmp;
	t_list		*new;

	instru = &(*champ)->instru;
	if (!(tmp = ft_itoa(swap_int(c))))
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
	}
	free(tmp);
}

static int		get_champ(t_champ **champ, char *path)
{
	int64_t		c;
	int			fd;
	int			ret;

	if (path)
	{
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			while ((ret = read(fd, &c, 4)))
				populate_instru(champ, c);
			close(fd);
			if (ret == -1)
				return (ERROR);
			if (check_champ(champ, path) == ERROR)
				return (ERROR);
		}
		else
		{
			ft_printf("{red}error : file '%s' does not exists{eoc}\n", path);
			return (ERROR);
		}
		return (SUCCESS);
	}
	return (ERROR);
}

static int		populate_champs(t_list **champs, char *path)
{
	t_list		*new;
	t_champ		*champ;

	champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (get_champ(&champ, path) == ERROR)
	{
		del_champ(champ, 0);
		return (ERROR);
	}
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

int				init_cor(t_cor *cor, char **argv)
{
	int			n;

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
	if (!(cor->map = malloc((MEM_SIZE + 1) * sizeof(unsigned char))))
		exit(EXIT_FAILURE);
	init_memory(cor);
	cor->cycle_to_die = CYCLE_TO_DIE;
	if (cor->opt->v && !init_ncurses(cor))
		return (ERROR);
	cycle(cor);
	return (SUCCESS);
}
