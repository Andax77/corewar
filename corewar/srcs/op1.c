/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:05:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/06/15 16:54:56 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	ft_live(t_cor *cor, t_champ *champ)
{
	int		p;

	p = (cor->map[++champ->pc] << 24) + (cor->map[++champ->pc] << 16) +
	(cor->map[++champ->pc] << 8) + cor->map[++champ->pc];
	++champ->pc;
	//ajouter un live dans la structure et faire le live de p
}

void	ft_ld(t_cor *cor, t_champ *champ)
{
	int r1;
	int v1;

	// r = recup_content();
	// v1 = recup_content();
}

void	ft_st(t_cor *cor, t_champ *champ)
{
	int r1;
	int v1;
}

void	ft_add(t_cor *cor, t_champ *champ)
{
	int r1;
	int r2;
	int r3;

}

void	ft_sub(t_cor *cor, t_champ *champ)
{
	int r1;
	int r2;
	int r3;

}
