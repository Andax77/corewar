/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instru.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:20:55 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/09 14:56:04 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		ft_clean_spaces_comments(t_instru *inst)
{
	int		i;
	int		j;
	int		k;
	char	*clean;

	i = -1;
	while (inst->params[++i])
	{
		j = -1;
		while (inst->params[i][++j] == ' ' || inst->params[i][j] == '\t')
			;
		k = ft_strlen(inst->params[i]) - 1;
		while (inst->params[i][k] == ' ' || inst->params[i][k] == '\t')
			--k;
		if (!(clean = ft_strndup(inst->params[i] + j, k - j + 1)))
			exit(EXIT_FAILURE);
		free(inst->params[i]);
		inst->params[i] = clean;
	}
}

static int		ft_verif_params(char **params)
{
	int		i;
	int		j;

	i = -1;
	while (params[++i])
		if (params[i][0] == DIRECT_CHAR)
		{
			if (params[i][1] == LABEL_CHAR)
			{
				j = 1;
				while (params[i][++j])
					if (!ft_strchr(LABEL_CHARS, params[i][j]))
						return (ERROR);
			}
			else if (!ft_strisdigit(params[i] + 1))
				return (ERROR);
		}
		else if (params[i][0] == LABEL_CHAR)
		{
			j = 0;
			while (params[i][++j])
				if (!ft_strchr(LABEL_CHARS, params[i][j]))
					return (ERROR);
		}
	return (SUCCESS);
}

int				ft_get_params(t_instru *inst, char *str)
{
	int		i;

	if (ft_check_params_format(inst, str) == ERROR)
		return (ERROR);
	str = ft_strstr(str, g_op_tab[inst->op_code - 1].name);
	i = -1;
	while (++i < (int)ft_strlen(g_op_tab[inst->op_code - 1].name))
		str++;
	if (inst->label_name && \
ft_strstr(inst->label_name, g_op_tab[inst->op_code - 1].name))
	{
		while (*str != LABEL_CHAR)
			str++;
		str = ft_strstr(str, g_op_tab[inst->op_code - 1].name);
		i = -1;
		while (++i < (int)ft_strlen(g_op_tab[inst->op_code - 1].name))
			str++;
	}
	if (!(inst->params = ft_strsplit(str, SEPARATOR_CHAR)))
		exit(EXIT_FAILURE);
	ft_clean_spaces_comments(inst);
	if (ft_verif_params(inst->params) == ERROR)
		return (ERROR);
//	i = -1;
//	while (inst->params[++i])
//		ft_printf("{green}%s, ", inst->params[i]);
//	ft_printf("\n{eoc}");
	return (SUCCESS);
}

void			ft_get_size_instruction(t_instru *inst)
{
	int		i;

	i = -1;
	inst->size += 1;
	inst->size += (inst->ocp != 0) ? 1 : 0;
	while (inst->params[++i])
	{
		if (ft_get_t_param(inst->params[i]) == T_REG)
			inst->size += 1;
		else if (ft_get_t_param(inst->params[i]) == T_IND)
			inst->size += 2;
		else if (ft_get_t_param(inst->params[i]) == T_DIR)
			inst->size += (g_op_tab[inst->op_code - 1].dir_size == 1) ? 2 : 4;
	}
}

int				ft_get_instru(t_champ *champ)
{
	t_list		*cur;
	t_instru	*inst;

	cur = champ->input;
	while (cur != NULL)
	{
		if (ft_empty_or_comment_line((char *)cur->content) == EMPTY)
		{
			cur = cur->next;
			continue ;
		}
		inst = ft_init_instru();
		if (ft_fill_instru(inst, (char*)cur->content) == ERROR)
		{
			ft_free_struct_instru(inst);
			return (ERROR);
		}
		ft_fill_lst_instru(champ, inst);
		free(inst);
		cur = cur->next;
	}
	return (SUCCESS);
}
