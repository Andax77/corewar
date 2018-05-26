/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/26 02:35:01 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		check_name(t_list* instru)
{
	int	i;

	i = 0;
	while (instru)
	{
		//if (i > PROG_NAME_LENGTH)
		//	return (ERROR);
		ft_printf("%s\n", instru->content);
		//i += ?????;
		instru = instru->next;
	}
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
	if (check_name(instru->next) == ERROR)
	{
		ft_printf("{red}error : champion '%s' has wrong name length{eoc}\n", \
			path);
		del_champ(*champ, 0);
		return (ERROR);
	}
	return (SUCCESS);
}
