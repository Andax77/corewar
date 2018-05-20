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

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		ft_printf("{red}%d\n{eoc}", cur->op_code);
//		printf("%p\n", tmp->content);
//		if (cur->label_name != NULL)
//			ft_printf("{red}%s\n{eoc}", cur->label_name);
		tmp = tmp->next;
	}
}
