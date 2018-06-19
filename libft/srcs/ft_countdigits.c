/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:28:01 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/23 23:17:49 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countdigits(long long n)
{
	int		count;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
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
