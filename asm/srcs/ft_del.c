/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:18:42 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/22 16:14:57 by pmilan           ###   ########.fr       */
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
	char		**tmp_tab;
	int			n;
	t_instru	*instru;

	(void)content_size;
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
	if (champ)
	{
		if (champ->name)
			free(champ->name);
		if (champ->comment)
			free(champ->comment);
		if (champ->input)
			ft_lstdel(&champ->input, del_input);
		if (champ->instru)
			ft_lstdel(&champ->instru, del_instru);
		free(champ);
	}
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
