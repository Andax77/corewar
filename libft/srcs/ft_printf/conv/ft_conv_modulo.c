/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_modulo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:30:17 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/22 14:36:11 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

int		ft_conv_modulo(char **ret, t_arg *arg)
{
	char	*tmp;
	int		size;

	size = 1;
	if (arg->wi > 0)
		size = arg->wi;
	if (!(tmp = ft_strnew(size)))
		return (ERROR);
	if (arg->flag.zero == 1)
		ft_memset(tmp, '0', size);
	else
		ft_memset(tmp, ' ', size);
	if (arg->flag.minus == 1)
		tmp[0] = '%';
	else
		tmp[size - 1] = '%';
	if (!(*ret = ft_strfreejoin(*ret, tmp, size, arg)) && ft_fruit(1, &tmp))
		return (ERROR);
	arg->cmpt += size;
	free(tmp);
	return (SUCCESS);
}
