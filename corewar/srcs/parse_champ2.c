/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:30:24 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/12 19:36:16 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		check_prog_len_else(t_list *instru, char *add, char **text)
{
	if (!(add = ft_itoa_base(ft_atoi(instru->content), 16)))
		exit(EXIT_FAILURE);
	if (ft_strlen(add) < 8)
		pad(&add, 8);
	ft_strcat(*text, add);
	ft_fruit(1, &add);
}
