/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fruit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:52:08 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/22 12:52:29 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

int		ft_fruit(size_t n, ...)
{
	void	**del;
	va_list	ap;

	va_start(ap, n);
	while (n-- > 0)
	{
		del = va_arg(ap, void **);
		free(*del);
		*del = NULL;
	}
	va_end(ap);
	return (1);
}
