/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzstrcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:42:42 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/12 19:45:00 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_bzstrcpy(char *dest, const char *src, size_t size)
{
	ft_bzero(dest, size);
	ft_strcpy(dest, src);
	return (dest);
}
