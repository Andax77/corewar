/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:33:48 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/12 15:38:52 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

void	ft_putstr_fd(char const *s, int fd)
{
	int length;

	if (s == NULL)
		return ;
	length = ft_strlen(s);
	write(fd, s, length);
}
