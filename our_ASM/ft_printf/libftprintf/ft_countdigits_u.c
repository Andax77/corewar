/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:28:01 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/13 23:43:45 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countdigits_u(unsigned long n)
{
	int		count;

	count = 1;
	if (n != 0)
	{
		while (n > 9)
		{
			n /= 10;
			count++;
		}
	}
	return (count);
}
