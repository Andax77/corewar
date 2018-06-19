/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:36:49 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/08 17:43:52 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

int			ft_vprintf(const char *format, va_list ap)
{
	char	*str;
	int		ret;

	str = NULL;
	ret = ft_vasprintf(&str, format, ap);
	if (ret != ERROR && str != NULL)
		if (write(STDOUT_FILENO, str, ret) == -1)
			ret = ERROR;
	free(str);
	return (ret);
}
