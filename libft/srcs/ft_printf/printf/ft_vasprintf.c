/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:11:40 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/26 17:07:35 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

int			ft_vasprintf(char **ret, const char *format, va_list ap)
{
	t_arg	arg;

	arg.cmpt = 0;
	if (ret == NULL)
		return (ERROR);
	if (ft_parse(ret, format, ap, &arg) == ERROR)
		return (ERROR);
	if (ft_color(ret, &arg) == ERROR)
		return (ERROR);
	return (arg.cmpt);
}
