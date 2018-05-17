/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:19:38 by pmilan            #+#    #+#             */
/*   Updated: 2017/12/18 16:19:52 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_power(double nb, int power)
{
	double result;

	result = nb;
	if (power <= 0)
	{
		while (power <= 0)
		{
			result /= nb;
			++power;
		}
		return (result);
	}
	while (power > 1)
	{
		result *= nb;
		--power;
	}
	return (result);
}
