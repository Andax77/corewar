/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/27 23:43:35 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static t_list	*check_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size + 1)))
		exit(EXIT_FAILURE);
	while (instru && (i += 4))
	{
		if (i == size)
		{
			if (ft_atoi(instru->content) != 0)
				return (NULL);
			else
				break ;
		}
		if (ft_atoi(instru->content) != 0)
		{
			add = translate(ft_atoi(instru->content));
			ft_strcat(*text, add);
			free(add);
		}
		instru = instru->next;
	}
	if (!instru)
		return (NULL);
	return (instru->next);
}

static int		check_prog_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size + 1)))
		exit(EXIT_FAILURE);
	while (instru && (i += 4))
	{
		if (i > size)
			return (ERROR);
		add = ft_itoa_base(ft_atoi(instru->content), 16);
		if (ft_strlen(add) < 8)
			padd(&add);
		ft_strcat(*text, add);
		free(add);
		instru = instru->next;
	}
	return (SUCCESS);
}

static int		check_champ_bis(t_list *instru, t_champ **champ, char *path)
{
	(*champ)->op_nb = ft_atoi(instru->content);
	if (!(instru = check_len(instru->next, COMMENT_LENGTH, &(*champ)->comment)))
	{
		ft_printf("{red}error : champion '%s' has wrong comment length{eoc}\n",\
			path);
		return (ERROR);
	}
	if (check_prog_len(instru->next, CHAMP_MAX_SIZE, &(*champ)->prog) == ERROR)
	{
		ft_printf("{red}error : champion '%s' has wrong length{eoc}\n",\
			path);
		return (ERROR);
	}
	//TODO Check prog (operations conformity)
	//DEBUG
	//ft_printf("champ name = %s, op_nb = %d, comment = %s, prog = %s\n", (*champ)->name, (*champ)->op_nb, (*champ)->comment, (*champ)->prog);
	return (SUCCESS);
}

int				check_champ(t_champ **champ, char *path)
{
	t_list	*instru;

	if (!(instru = (*champ)->instru))
	{
		ft_printf("{red}error : champion '%s' is empty{eoc}\n", path);
		return (ERROR);
	}
	if (ft_atoi(instru->content) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("{red}error : champion '%s' has wrong CEM{eoc}\n", path);
		return (ERROR);
	}
	if (!(instru = check_len(instru->next, PROG_NAME_LENGTH, &(*champ)->name)))
	{
		ft_printf("{red}error : champion '%s' has wrong name length{eoc}\n", \
			path);
		return (ERROR);
	}
	if (check_champ_bis(instru->next, champ, path) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
