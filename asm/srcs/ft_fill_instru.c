/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_instru.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:08:11 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/20 15:08:11 by pierremilan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		ft_fill_label_addr(t_champ *champ)
{
	t_list		*tmp;
	t_instru	*cur;
	int			total_size;

	tmp = champ->instru;
	total_size = 0;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		ft_printf("{red}%s{eoc}\n", cur->label_name);
//		if (cur->label_name != NULL)
		cur->label_addr = total_size;
		ft_printf("{blue}%d\n{eoc}", cur->label_addr);
		total_size += cur->size;
		tmp = tmp->next;
	}
}

int				ft_fill_instru(t_instru *inst, char *str)
{
	if (ft_get_label_name(inst, str) == ERROR)
		return (ERROR);
	ft_get_op_code(inst, str);
	if (inst->op_code != 0)
	{
		if (ft_get_params(inst, str) == ERROR)
			return (ERROR);
		if (ft_get_ocp(inst) == ERROR)
			return (ERROR);
		ft_get_size_instruction(inst);
	}
	return (SUCCESS);
}
