/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:26:32 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/12 15:34:08 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

void	ft_putstr(char const *str)
{
	int length;

	if (str == NULL)
		return ;
	length = ft_strlen(str);
	write(STDOUT_FILENO, str, length);
}
