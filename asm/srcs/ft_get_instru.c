/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instru.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:20:55 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/18 19:04:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		ft_empty_line(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\v'
											&& str[i] != '\n' && str[i] != '\f')
			return (CHARACTER);
	}
	return (EMPTY);
}

int				ft_get_label_name(t_instru *inst, char *str)
{
	int		i;

	i = -1;
	if (ft_strchr(str, ':'))
	{
		while (str[++i] && str[i] != ':')
			;
		if (!(inst->label_name = ft_strndup(str, i)))
			exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

int				ft_fill_instru(t_instru *inst, char *str)
{
	if (ft_get_label_name(inst, str) == ERROR)
		return (ERROR);
	if (ft_get_op_code(inst, str) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int				ft_get_instru(t_champ *champ)
{
	t_list		*cur;
	t_instru	*inst;
	t_list		*new;

	cur = champ->input;
	while (cur != NULL)
	{
		if (ft_empty_line(cur->content) == EMPTY)
		{
			cur = cur->next;
			continue ;
		}
		inst = ft_init_instru();
		ft_fill_instru(inst, (char*)cur->content);
		if (!champ->instru)
		{
			if (!(champ->instru = ft_lstnew(inst, sizeof(t_instru *))))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(new = ft_lstnew(inst, sizeof(t_instru *))))
				exit(EXIT_FAILURE);
			ft_lstaddend(&champ->instru, new);
		}
		free(inst);
		cur = cur->next;
	}
	return (SUCCESS);
}
