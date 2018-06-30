/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 01:30:10 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/09 16:42:44 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int16_t		swap_int16(int16_t val)
{
	return ((val << 8) | ((val >> 8) & 0xFF));
}

int32_t		swap_int32(int32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | ((val >> 16) & 0xFFFF));
}

int64_t		swap_int64(int64_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | ((val >> 16) & 0xFFFF));
}

char		*translate(int64_t val)
{
	char	*text;

	if (!(text = ft_strnew(5)))
		exit(EXIT_FAILURE);
	text[0] = val >> 24;
	text[1] = val >> 16;
	text[2] = val >> 8;
	text[3] = val & 0x000000FF;
	text[4] = '\0';
	return (text);
}

int			pad(char **str, int n)
{
	char	*tmp;
	char	zeros[n + 1];
	int		i;
	int		len;

	i = 0;
	len = n - ft_strlen(*str);
	tmp = *str;
	while (len--)
		zeros[i++] = '0';
	while (i <= n)
		zeros[i++] = '\0';
	if (!(*str = ft_strjoin(zeros, *str)))
		exit(EXIT_FAILURE);
	free(tmp);
	return (SUCCESS);
}
