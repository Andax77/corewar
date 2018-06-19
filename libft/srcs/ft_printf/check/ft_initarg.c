/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:38:57 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/04 18:39:42 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

void		ft_initarg(t_arg *arg)
{
	arg->arg.d = 0;
	arg->height[0] = '\0';
	arg->conv = '\0';
	arg->flag.hashtag = 0;
	arg->flag.minus = 0;
	arg->flag.plus = 0;
	arg->flag.zero = 0;
	arg->flag.space = 0;
	arg->wi = 0;
	arg->preci = -1;
	arg->str = NULL;
}
