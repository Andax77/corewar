/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 19:16:36 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 19:18:53 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		ft_print_error(char *msg, char *path)
{
	if (!path)
		ft_printf("{red}%s\n{eoc}", msg);
	else
		ft_printf("{red}error : '%s' %s{eoc}\n", path, msg);
	return (ERROR);
}
