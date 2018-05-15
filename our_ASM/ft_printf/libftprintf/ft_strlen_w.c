/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:00:21 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/08 22:21:18 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_w(const wchar_t *s)
{
	unsigned int i;
	unsigned int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] <= 128)
			len++;
		else if (s[i] <= 2047)
			len += 2;
		else if (s[i] <= 65535)
			len += 3;
		else
			len += 4;
		i++;
	}
	return (len);
}
