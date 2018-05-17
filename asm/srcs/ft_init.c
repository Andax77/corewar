/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:33:26 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/17 19:33:51 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	ft_init(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->input = NULL;
//	champ->instru = NULL;
	champ->fd = 0;
}
