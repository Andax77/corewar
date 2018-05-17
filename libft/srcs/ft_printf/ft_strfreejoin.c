/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreejoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:03:05 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/22 14:29:38 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

char		*ft_strfreejoin(char *s1, const char *s2, int size_s2, t_arg *arg)
{
	char	*retour;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = arg->cmpt;
	lens2 = size_s2;
	if (!(retour = (char *)malloc(sizeof(*retour) * (lens1 + size_s2 + 1))))
		return (NULL);
	i = -1;
	while (++i < lens1)
		retour[i] = s1[i];
	i--;
	while (++i < lens1 + size_s2)
		retour[i] = s2[i - lens1];
	retour[i] = '\0';
	ft_fruit(1, &s1);
	return (retour);
}
