/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:51:05 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/10 15:10:28 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		y;

	if (to_find[0] == 0)
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		y = 0;
		while (str[i + y] == to_find[y])
		{
			if (to_find[y + 1] == '\0')
				return (&((char *)str)[i]);
			y++;
		}
		i++;
	}
	return (0);
}
