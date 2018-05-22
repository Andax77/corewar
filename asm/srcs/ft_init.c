/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:33:26 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/22 16:10:59 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		ft_init_champ(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->input = NULL;
	champ->instru = NULL;
	champ->fd = 0;
}

t_instru	*ft_init_instru(void)
{
	t_instru	*inst;

	inst = ft_malloc(sizeof(t_instru), EXIT_FAILURE);
	inst->params = NULL;
	inst->label_name = NULL;
	inst->op_code = 0;
	inst->ocp = 0;
	inst->size = 0;
	inst->inst_addr = 0;
	return (inst);
}
