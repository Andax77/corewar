/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:50:35 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/09 17:26:09 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "../libftprintf/libft.h"
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_tmp
{
	long long	nbr;
	char		*c;
	wchar_t		*wc;
}				t_tmp;

int				ft_printf(const char *format, ...);
int				ft_if_forest(char **types, va_list ap, int j, int *p_ret);
int				ft_parse_f_flags(char **types, int i, int j, int *f_tab);
int				ft_parse_c_flags(char **types, int i, int j, int *f_tab);
int				ft_no_flags(char types, int *f_tab, int *p_ret);
void			ft_parse_di(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_lld(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_x(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_llx(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_o(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_llo(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_u(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_llu(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_p(va_list ap, int *p_ret, int *f_tab, long long tmp);
void			ft_parse_c(va_list ap, int *p_ret, int *f_tab);
void			ft_parse_llc(va_list ap, int *p_ret, int *f_tab);
void			ft_parse_s(va_list ap, int *p_ret, int *f_tab, char *tmp_s);
void			ft_parse_lls(va_list ap, int *p_rt, int *f_tb, wchar_t *tmp_ws);

#endif
