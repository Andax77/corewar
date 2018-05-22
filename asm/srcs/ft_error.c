/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 00:44:20 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/22 00:44:20 by pierremilan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		ft_error(t_champ *champ, char *msg)
{
	ft_printf("{red}%s{eoc}\n", msg);
	del_champ(champ);
	exit(EXIT_FAILURE);
}
