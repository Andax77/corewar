/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/04 15:31:18 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int64_t					swap_int(int64_t c)
{
	c = ((c << 8) & 0xFF00FF00) | ((c >> 8) & 0xFF00FF);
	return ((c << 16) | ((c >> 16) & 0xFFFF));
}

char					*translate(int64_t val)
{
	char	*text;
	int		i;

	i = 0;
	if (!(text = ft_strnew(5)))
		exit(EXIT_FAILURE);
	text[0] = val >> 24;
	text[1] = val >> 16;
	text[2] = val >> 8;
	text[3] = val & 0x000000FF;
	text[4] = '\0';
	return (text);
}

int						pad(char **str, int n)
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

static unsigned char	get_hex_val(char a, char b)
{
	unsigned char	res;
	unsigned char	n;
	unsigned char	k;

	n = 0;
	k = 0;
	if (b >= '0' && b <= '9')
		n = b - 48;
	else if (b >= 'a' && b <= 'f')
		n = b + 10 - 97;
	if (a >= '0' && a <= '9')
		k = a - 48;
	else if (a >= 'a' && a <= 'f')
		k = a + 10 - 97;
	if (k == 0)
		res = n;
	else if (n == 0)
		res = 16 * k;
	else
		res = (16 * k) + n;
	return (res);
}

void					split_bits(char **prog, unsigned char **splited_prog)
{
	unsigned char	*splited;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!(splited = (unsigned char *)malloc((ft_strlen(*prog) / 2) + 1 * \
					sizeof(unsigned char))))
		exit(EXIT_FAILURE);
	while ((*prog)[i] && j < (int)ft_strlen(*prog))
	{
		if (i && i % 2)
		{
			splited[j] = get_hex_val((*prog)[i - 1], (*prog)[i]);
			j++;
		}
		i++;
	}
	splited[j] = '\0';
	*splited_prog = splited;
}
