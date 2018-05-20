/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:18:42 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/20 21:28:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	del_input(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
		free(content);
}

static void	del_instru(void *content, size_t content_size)
{
	char	**tmp_tab;
	int		n;
	(void)content_size;
	t_instru	*instru;

	instru = (t_instru*)content;
	tmp_tab = (char**)instru->params;
	n = 0;
	while (tmp_tab && tmp_tab[n])
	{
		free(tmp_tab[n]);
		n++;
	}
	if (instru->label_name)
		free(instru->label_name);
	free(tmp_tab);
	free(content);
}

void		del_champ(t_champ *champ)
{
	free(champ->name);
	free(champ->comment);
	ft_lstdel(&champ->input, del_input);
	ft_lstdel(&champ->instru, del_instru);
	free(champ);
}

void		ft_free_struct_instru(t_instru *inst)
{
	int		i;

	i = -1;
	while (inst->params[++i])
		free(inst->params[i]);
	free(inst->params);
	free(inst->label_name);
	free(inst);
}
