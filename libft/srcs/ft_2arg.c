/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:52:27 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/15 14:12:35 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_2arg(int arg1, int arg2)
{
	int		bit;

	bit = sizeof(long long) * 4;
	return (((unsigned long)((long)arg1 << bit) >> bit) + ((long)arg2 << bit));
}
