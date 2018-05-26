/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/26 19:37:39 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

char	*translate(uint64_t val)
{
	char	*text;

	if (!(text = ft_strnew(4)))
		exit(EXIT_FAILURE);
	(val >> 24) ? text[0] = val >> 24 : 0;
	(val >> 16) ? text[1] = val >> 16 : 0;
	(val >> 8) ? text[2] = val >> 8 : 0;
	(val & 0x000000FF) ? text[3] = val & 0x000000FF : 0;
	return (text);
}

static t_list	*check_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	*text = ft_strnew(size);
	while (instru && (i += 4))
	{
		if (i == size)
		{
			if (ft_atoi(instru->content) != 0)
				return (NULL);
			else
			{
				instru = instru->next;
				break ;
			}
		}
		if (ft_atoi(instru->content) != 0)
		{
			add = translate(ft_atoi(instru->content));
			ft_strcat(*text, add);
			free(add);
		}
		instru = instru->next;
	}
	return (instru);
}

int		check_champ(t_champ **champ, char *path)
{
	t_list	*instru;

	if (!(instru = (*champ)->instru))
	{
		ft_printf("{red}error : champion '%s' is empty{eoc}\n", path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	if (ft_atoi(instru->content) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("{red}error : champion '%s' has wrong CEM{eoc}\n", path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	if (!(instru = check_len(instru->next, PROG_NAME_LENGTH, &(*champ)->name)))
	{
		ft_printf("{red}error : champion '%s' has wrong name length{eoc}\n", \
			path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	(*champ)->op_nb = ft_atoi(instru->next->content);
	if (!(instru = check_len(instru->next, COMMENT_LENGTH, &(*champ)->comment)))
	{
		ft_printf("{red}error : champion '%s' has wrong comment length{eoc}\n",\
			path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	ft_printf("champ name = %s, op_nb = %d, comment = %s\n", (*champ)->name, (*champ)->op_nb, (*champ)->comment);
	return (SUCCESS);
}
