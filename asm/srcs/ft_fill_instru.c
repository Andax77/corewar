/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_instru.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:08:11 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/22 17:11:49 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	ft_get_addr_label(t_champ *champ, char *str)
{
	t_list		*tmp;
	t_instru	*cur;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if (cur->label_name)
			if (ft_strcmp(cur->label_name, str) == 0)
				return (cur->inst_addr);
		tmp = tmp->next;
	}
	return (ERROR);
}

static void	ft_replace_direct_param(t_champ *champ, t_instru *cur, int i)
{
	int			addr;
	int			len;

	if ((addr = ft_get_addr_label(champ, cur->params[i] + 2)) == ERROR)
		ft_error(champ, "error: direct address has no match");
	addr -= cur->inst_addr;
	free(cur->params[i]);
	if (!(cur->params[i] = ft_itoa(addr)))
		exit(EXIT_FAILURE);
	len = ft_strlen(cur->params[i]);
	if (!(cur->params[i] = ft_realloc(cur->params[i], len + 1, len + 2)))
		exit(EXIT_FAILURE);
	ft_memmove(cur->params[i] + 1, cur->params[i], len + 1);
	cur->params[i][0] = DIRECT_CHAR;
}

void		ft_replace_direct(t_champ *champ)
{
	int			i;
	t_list		*tmp;
	t_instru	*cur;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if (cur->params)
		{
			i = -1;
			while (cur->params[++i])
				if (ft_get_t_param(cur->params[i]) == T_DIR &&
										ft_strchr(cur->params[i], LABEL_CHAR))
					ft_replace_direct_param(champ, cur, i);
		}
		tmp = tmp->next;
	}
}

void		ft_fill_inst_addr(t_champ *champ)
{
	t_list		*tmp;
	t_instru	*cur;
	int			total_size;

	tmp = champ->instru;
	total_size = 0;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		cur->inst_addr = total_size;
		total_size += cur->size;
		tmp = tmp->next;
	}
}

int			ft_fill_instru(t_instru *inst, char *str)
{
	if (ft_get_label_name(inst, str) == ERROR)
		return (ERROR);
	if (ft_get_op_code(inst, str) == ERROR)
		return (ERROR);
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
