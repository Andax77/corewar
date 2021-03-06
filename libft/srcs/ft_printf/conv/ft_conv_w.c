/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 20:07:41 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 16:45:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

static int	ft_fruit2(char *str, char *mantisse, char *exp_new_ret)
{
	free(str);
	free(mantisse);
	free(exp_new_ret);
	return (SUCCESS);
}

static int	ft_nb_len(int nb)
{
	int		nb_len;

	nb_len = (nb < 0) ? 2 : 1;
	while (nb /= 10)
		nb_len++;
	return (nb_len);
}

static char	*ft_clean_zero(char *mantisse)
{
	int		i;
	int		count;
	char	*cpy;

	if (mantisse == NULL)
		return (NULL);
	i = 52;
	count = 0;
	while (mantisse[--i] == '0')
		count++;
	if (!(cpy = (char *)malloc(sizeof(*cpy) * (57 - count))))
		return (NULL);
	cpy[56 - count] = '\0';
	cpy[0] = '1';
	cpy[1] = '.';
	i = -1;
	while (++i < 52 - count)
		cpy[i + 2] = mantisse[i];
	cpy[i + 2] = '|';
	cpy[i + 3] = '2';
	if (!(mantisse = ft_strdup(cpy)))
		return (NULL);
	free(cpy);
	return (mantisse);
}

static int	ft_conv_w2(char **str, int size, int size_e, long long exposant_f)
{
	free(*str);
	if (!(*str = (char *)malloc(sizeof(char) * (size + 1))))
		return (ERROR);
	ft_strcpy(*str + 1, "2e");
	(*str)[3] = ((exposant_f *= 10) == 0) ? '0' : '-';
	(*str)[3 + size_e] = '*';
	(*str)[4 + size_e] = '\0';
	while (--size_e >= 0 && (exposant_f /= 10) != 0)
		(*str)[3 + size_e] = exposant_f % 10 + '0';
	return (SUCCESS);
}

int			ft_conv_w(char **ret, t_arg *arg, int size, int size_exposant)
{
	t_f			f;
	long long	exposant_f;
	char		*str;
	char		*mantisse;
	char		*exp_new_ret;

	f.f = arg->arg.f;
	if ((!(str = ft_int_to_nbase(f.l, "01", 64)))
			|| (!(exp_new_ret = ft_strndup(str + 1, 11))))
		return (ERROR);
	exposant_f = ft_base_to_int(exp_new_ret, "01") - 1023;
	size_exposant = ft_nb_len(exposant_f);
	exposant_f = (exposant_f < 0) ? -(t_ull)exposant_f : (t_ull)exposant_f;
	if (!(mantisse = ft_clean_zero(ft_strndup(str + 12, 52))))
		return (ERROR);
	size = ft_strlen(mantisse) + size_exposant + 4;
	if (ft_conv_w2(&exp_new_ret, size, size_exposant, exposant_f) == ERROR)
		return (ERROR);
	if (exp_new_ret)
		exp_new_ret[0] = (str[0] == '0') ? '+' : '-';
	ft_strncat(exp_new_ret, mantisse, ft_strlen(mantisse));
	if (!(*ret = ft_strfreejoin(*ret, exp_new_ret, size, arg)))
		return (ERROR);
	arg->cmpt += size;
	return (ft_fruit2(str, mantisse, exp_new_ret));
}
