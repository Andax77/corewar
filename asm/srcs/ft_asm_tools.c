/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:11:05 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/12 14:58:57 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

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

unsigned char			*split_bits(char *prog)
{
	unsigned char	*splitted_prog;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!(splitted_prog = (unsigned char *)malloc((ft_strlen(prog) / 2) + 1 * \
					sizeof(unsigned char))))
		exit(EXIT_FAILURE);
	while (prog[i] && j < (int)ft_strlen(prog))
	{
		if (i && i % 2)
		{
			splitted_prog[j] = get_hex_val(prog[i - 1], prog[i]);
			j++;
		}
		i++;
	}
	splitted_prog[j] = '\0';
	return (splitted_prog);
}
