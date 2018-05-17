/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:42:38 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/12 15:55:13 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	if (s == NULL)
		return (NULL);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	if (!(i = 0) && *s == 0)
		return (ft_strnew(1));
	while (!(j = 0) && s[i])
		i++;
	k = --i;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i--)
		j++;
	if (!(ret = (char*)(malloc(sizeof(*ret) * (k - j + 2)))))
		return (NULL);
	i = -1;
	while (++i <= (k - j))
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}
