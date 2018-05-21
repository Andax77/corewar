/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_instru.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 19:14:16 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/21 18:48:11 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		ft_check_ocp_addition(int total, int num)
{
	if (total == 1 && num != 1)
		return (ERROR);
	else if (total == 2 && num != 2)
		return (ERROR);
	else if (total == 3 && !(num == 1 || num == 2))
		return (ERROR);
	else if (total == 5 && !(num == 1 || num == 4))
		return (ERROR);
	else if (total == 6 && !(num == 2 || num == 4))
		return (ERROR);
	else if (total == 7 && !(num == 1 || num == 2 || num == 4))
		return (ERROR);
	return (SUCCESS);
}

int				ft_check_params_type(t_instru *inst)
{
	int		i;

	i = -1;
	while (inst->params[++i])
		;
	if (i != g_op_tab[inst->op_code - 1].nb_params)
		return (ERROR);
	i = -1;
	while (inst->params[++i])
	{
		if (ft_get_t_param(inst->params[i]) == ERROR ||
			ft_check_ocp_addition(g_op_tab[inst->op_code - 1].params_type[i],
			ft_get_t_param(inst->params[i])) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int				ft_check_params_format(t_instru *inst, char *str)
{
	int		nb_params;
	int		i;
	int		count_separators;

	nb_params = g_op_tab[inst->op_code - 1].nb_params;
	i = -1;
	count_separators = 0;
	while (str[++i] && str[i] != COMMENT_CHAR)
		if (str[i] == SEPARATOR_CHAR)
			++count_separators;
	if (count_separators == nb_params - 1)
		return (SUCCESS);
	return (ERROR);
}
