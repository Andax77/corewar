/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/18 14:30:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_count_args(const char *format)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
			count++;
		i++;
	}
	return (count);
}

static int		ft_odd(const char *format, int i)
{
	int n;

	n = 0;
	while (i >= 0 && format[i] == '%')
	{
		n++;
		i--;
	}
	if (n % 2 == 0)
		return (0);
	else
		return (1);
}

static void		ft_get_type(const char *format, char **types)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(format))
	{
		if (format[i] == '%' && format[i + 1] != '%' && ft_odd(format, i))
		{
			types[j] = ft_strdup(format + i + 1);
			j++;
		}
		i++;
	}
	types[j] = NULL;
}

static int		ft_process(const char *format, char **types, va_list ap)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 0;
	while (i < (int)ft_strlen(format))
	{
		if (format[i] == '%' && format[i + 1] == '%')
			ret += ft_putchar(format[i++]);
		if (format[i] && format[i + 1] && format[i] == '%' && \
		format[i + 1] != '%' && ft_odd(format, i))
			i += ft_if_forest(types, ap, j++, &ret);
		else if (i >= 2 && format[i] != '%' && \
		format[i - 1] == '%' && format[i - 2] == '%')
			ret += ft_putchar(format[i]);
		else if (format[i] && i == 0 && format[i] != '%')
			ret += ft_putchar(format[i]);
		else if (format[i] && format[i - 1] && format[i] != '%' && \
		format[i - 1] != '%')
			ret += ft_putchar(format[i]);
		i++;
	}
	return (ret);
}

int				ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ac;
	int		ret;
	int		i;
	char	**types;

	i = 0;
	types = NULL;
	ret = 0;
	if (format == NULL)
		return (0);
	ac = ft_count_args(format);
	if (!(types = (char **)malloc(sizeof(char *) * (ac + 1))))
		return (-1);
	types[ac] = NULL;
	ft_get_type(format, types);
	va_start(ap, format);
	ret = ft_process(format, types, ap);
	va_end(ap);
	while (types[i])
		free(types[i++]);
	free(types);
	return (ret);
}
