/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits_oct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:28:01 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/27 17:45:52 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countdigits_oct(unsigned long n)
{
	int		count;

	count = 1;
	if (n != 0)
	{
		while (n > 7)
		{
			n /= 8;
			count++;
		}
	}
	return (count);
}
