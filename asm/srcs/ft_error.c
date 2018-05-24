/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 00:44:20 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/24 20:44:33 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			ft_error(t_champ *champ, char *msg)
{
	ft_printf("{red}file: %s -> %s{eoc}\n", champ->argv, msg);
	del_champ(champ);
	return (ERROR);
}
