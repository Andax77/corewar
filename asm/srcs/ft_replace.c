/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 12:18:34 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 18:33:10 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		ft_get_addr_label(t_champ *champ, char *str)
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

static int		ft_replace_direct_param(t_champ *champ, t_instru *cur, int i)
{
	int			addr;
	int			len;

	if ((addr = ft_get_addr_label(champ, cur->params[i] + 2)) == ERROR)
		return (ft_error(champ, "error: direct address has no match"));
	addr -= cur->inst_addr;
	free(cur->params[i]);
	if (!(cur->params[i] = ft_itoa(addr)))
		exit(EXIT_FAILURE);
	len = ft_strlen(cur->params[i]);
	if (!(cur->params[i] = ft_realloc(cur->params[i], len + 1, len + 2)))
		exit(EXIT_FAILURE);
	ft_memmove(cur->params[i] + 1, cur->params[i], len + 1);
	cur->params[i][0] = DIRECT_CHAR;
	return (SUCCESS);
}

static int		ft_replace_indirect_param(t_champ *champ, t_instru *cur, int i)
{
	int			addr;

	if ((addr = ft_get_addr_label(champ, cur->params[i] + 1)) == ERROR)
		return (ft_error(champ, "error: indirect address has no match"));
	addr -= cur->inst_addr;
	free(cur->params[i]);
	if (!(cur->params[i] = ft_itoa(addr)))
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

static int		ft_replace_direct(t_champ *champ)
{
	int			i;
	t_list		*tmp;
	t_instru	*cur;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if ((i = -1) && cur->params)
		{
			while (cur->params[++i])
				if (ft_get_t_param(cur->params[i]) == T_DIR
						&& ft_strchr(cur->params[i], LABEL_CHAR))
				{
					if (ft_replace_direct_param(champ, cur, i) == ERROR)
						return (ERROR);
				}
				else if (ft_get_t_param(cur->params[i]) == T_IND
						&& ft_strchr(cur->params[i], LABEL_CHAR))
					if (ft_replace_indirect_param(champ, cur, i) == ERROR)
						return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int				ft_fill_inst_addr_and_replace_direct(t_champ *champ)
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
	if (ft_verif_register(champ) == ERROR)
		return (ERROR);
	return (ft_replace_direct(champ));
}
