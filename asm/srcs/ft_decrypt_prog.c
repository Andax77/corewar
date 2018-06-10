/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decrypt_prog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:05:18 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/10 20:19:12 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			ft_decrypt_prog(t_champ *champ, unsigned char *prog, int inst_length)
{
	int		i;

	i = 0;
	while (i < inst_length)
	{
		//reprendre les fonctions de tools2 pour check op_code->ocp
		//remplir un t_instru au fur et a mesure et le mettre dans une liste chainee
		ft_printf("{red}%x {eoc}", prog[i]);
		++i;
	}
	return (SUCCESS);
}
