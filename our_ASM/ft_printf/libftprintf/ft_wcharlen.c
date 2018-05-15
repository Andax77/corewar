/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:00:21 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/08 18:00:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcharlen(const wchar_t c)
{
	unsigned int len;

	len = 0;
	if (c)
	{
		if (c <= 128)
			len++;
		else if (c <= 2047)
			len += 2;
		else if (c <= 65535)
			len += 3;
		else
			len += 4;
	}
	return (len);
}
