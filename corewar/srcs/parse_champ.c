/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/26 18:01:11 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		check_name(t_champ **champ, t_list *instru)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (instru)
	{
		if (i == PROG_NAME_LENGTH)
		{
			if (ft_atoi(instru->content) != 0)
				return (ERROR);
			else
				break ;
		}
		i += 4;
		if (ft_atoi(instru->content) != 0)
		{
			ft_printf("%x\n", ft_atoi(instru->content));
			//get_text();
		}
		instru = instru->next;
	}
	(*champ)->name = name;
	return (SUCCESS);
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
	if (check_name(champ, instru->next) == ERROR)
	{
		ft_printf("{red}error : champion '%s' has wrong name length{eoc}\n", \
			path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	return (SUCCESS);
}
