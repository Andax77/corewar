/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:11:42 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/16 16:32:02 by pmilan           ###   ########.fr       */
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
		((t_champ*)champs->content)->father = 0;
		((t_champ*)champs->content)->cur_op = 0;
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

static void		populate_instru(t_champ **champ, int64_t ch)
{
	t_list		**instru;
	char		*tmp;
	t_list		*new;

	instru = &(*champ)->instru;
	if (!(tmp = ft_itoa(swap_int(ch))))
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

static int		get_champ(t_champ **champ, char *path, int nb)
{
	int64_t		ch;
	int			fd;
	int			ret;
	int			cond;

	cond = 0;
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		while ((ret = read(fd, &ch, 4)))
		{
			++cond;
			if (cond == 1 && ret < 4)
				return (ft_print_error("not enough data", path));
			populate_instru(champ, ch);
		}
		close(fd);
		if (ret == -1)
			return (ERROR);
		if (check_champ(champ, path, nb) == ERROR)
			return (ERROR);
	}
	else
		return (ft_print_error("file does not exist", path));
	return (SUCCESS);
}

int				populate_champs(t_list **champs, char *path, int nb)
{
	t_list		*new;
	t_champ		*champ;

	champ = ft_malloc(sizeof(t_champ), EXIT_FAILURE);
	if (get_champ(&champ, path, nb) == ERROR)
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
	if (read_args(cor, argv) == ERROR)
		return (ERROR);
	if (MEM_SIZE > 0 && CYCLE_TO_DIE > 0 && CYCLE_DELTA > 0 && NBR_LIVE > 0
			&& MAX_CHECKS > 0 && REG_NUMBER > 0)
	{
		cor->aff = NULL;
		cor->winner = 0;
		cor->cycle_to_die = CYCLE_TO_DIE;
		cor->map = ft_malloc((MEM_SIZE + 1)
				* sizeof(unsigned char), EXIT_FAILURE);
		init_memory(cor);
		init_cmap(cor);
		if (MAX_PLAYERS > 4
				|| (!cor->opt->d && cor->opt->v && !init_ncurses(cor)))
			return (ERROR);
		print_intro(cor);
		(ft_lstcount(cor->champs) > 1) ? order_to_start(&cor->champs) : 0;
		cycle(cor, 1);
		return (SUCCESS);
	}
	ft_printf("{red}Wrong value in op.h\n{eoc}");
	return (ERROR);
}
