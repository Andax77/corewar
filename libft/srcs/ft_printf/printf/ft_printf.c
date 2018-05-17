/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:08:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/08 17:42:38 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*str;
	int		ret;

	str = NULL;
	va_start(ap, format);
	ret = ft_vasprintf(&str, format, ap);
	va_end(ap);
	if (ret != ERROR && str != NULL)
		if (write(STDOUT_FILENO, str, ret) == -1)
			ret = ERROR;
	free(str);
	return (ret);
}
