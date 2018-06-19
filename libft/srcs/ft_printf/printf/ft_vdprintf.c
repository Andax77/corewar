/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:34:40 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/08 17:43:27 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

int			ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*str;
	int		ret;

	str = NULL;
	ret = ft_vasprintf(&str, format, ap);
	if (ret != ERROR && str != NULL)
		if (write(fd, str, ret) == -1)
			ret = ERROR;
	free(str);
	return (ret);
}
