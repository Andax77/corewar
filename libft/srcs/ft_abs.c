/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:31:41 by pmilan            #+#    #+#             */
/*   Updated: 2017/12/12 11:32:36 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned	ft_abs(int nb)
{
	return ((nb < 0) ? -(unsigned int)nb : (unsigned int)nb);
}
