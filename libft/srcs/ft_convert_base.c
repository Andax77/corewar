/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:58:15 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/04 13:58:18 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char		*ft_convert_base(char *n, char *base_in, char *base_out)
{
	long long	int_nb;
	char		*ret;

	int_nb = ft_base_to_int(n, base_in);
	if (!(ret = ft_int_to_base(int_nb, base_out)))
		return (NULL);
	return (ret);
}
