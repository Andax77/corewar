/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/31 17:05:24 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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
	else if (b >= 'A' && b <= 'F')
		n = b - 55;
	if (a >= '0' && a <= '9')
		k = a - 48;
	else if (a >= 'A' && a <= 'F')
		k = a - 55;
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
	int		i;
	int		j;

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
