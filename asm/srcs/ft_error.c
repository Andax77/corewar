/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 00:44:20 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 16:23:55 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			ft_error(t_champ *champ, char *msg)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	while ((ret = get_next_line(champ->fd, &tmp)) != GNL_END)
		ft_fruit(1, &tmp);
	if (ret == GNL_ERROR)
		ft_fruit(1, &tmp);
	ft_printf("{red}file: %s -> %s{eoc}\n", champ->argv, msg);
	del_champ(champ);
	return (ERROR);
}

int			ft_error_m(t_champ *champ, char *msg)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ft_printf("{red}%s{eoc}\n", msg);
	ft_printf("{yellow}Please press ^d{eoc}\n");
	while ((ret = get_next_line(STDIN_FILENO, &tmp)) != GNL_END)
	{
		ft_printf("{yellow}Please press ^d{eoc}\n");
		ft_fruit(1, &tmp);
	}
	if (ret == GNL_ERROR)
		ft_fruit(1, &tmp);
	del_champ(champ);
	return (ERROR);
}
