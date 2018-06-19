/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_instru_annexe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:05:47 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 15:41:51 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		ft_fill_lst_instru(t_champ *champ, t_instru *inst)
{
	t_list		*new;

	new = NULL;
	if (!champ->instru)
	{
		if (!(champ->instru = ft_lstnew(inst, sizeof(t_instru))))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(new = ft_lstnew(inst, sizeof(t_instru))))
			exit(EXIT_FAILURE);
		ft_lstaddend(&(champ->instru), new);
	}
}

int			ft_get_t_param(char *str)
{
	if (str[0] == 'r')
		return (T_REG);
	else if (str[0] == DIRECT_CHAR)
		return (T_DIR);
	else if (ft_strisdigit(str))
		return (T_IND);
	return (ERROR);
}

int			ft_get_param_code(int num)
{
	if (num == T_REG)
		return (REG_CODE);
	else if (num == T_DIR)
		return (DIR_CODE);
	return (IND_CODE);
}
