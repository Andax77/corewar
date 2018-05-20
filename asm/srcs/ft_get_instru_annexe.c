/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instru_annexe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 19:20:59 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/20 19:20:59 by pierremilan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int				ft_get_label_name(t_instru *inst, char *str)
{
	int		i;

	i = -1;
	if (ft_strchr(str, LABEL_CHAR))
	{
		while (str[++i] && str[i] != LABEL_CHAR)
			;
		if (!(inst->label_name = ft_strndup(str, i)))
			exit(EXIT_FAILURE);
		i = -1;
		while (g_op_tab[++i].name && !(strstr(inst->label_name, g_op_tab[i].name)))
			;
		if (g_op_tab[i].name && strchr(inst->label_name, DIRECT_CHAR))
		{
			ft_fruit(1, &inst->label_name);
			return (SUCCESS);
		}
		i = -1;
		while (inst->label_name[++i])
			if (!ft_strchr(LABEL_CHARS, inst->label_name[i]))
				return (ERROR);
	}
	return (SUCCESS);
}

void			ft_get_op_code(t_instru *inst, char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	while (g_op_tab[++i].name)
	{
		if ((ptr = ft_strstr(str, g_op_tab[i].name)))
		{
			j = 0;
			while (ptr[j] && ptr[j] == g_op_tab[i].name[j])
				++j;
			if (ptr[j] && ptr[j] != LABEL_CHAR)
				inst->op_code = g_op_tab[i].op_code;
			if (ptr[j] && ptr[j] == LABEL_CHAR)
			{
				if (ft_strstr(ptr + j, g_op_tab[i].name))
					inst->op_code = g_op_tab[i].op_code;
			}
		}
	}
}

int				ft_get_t_param(char *str)
{
	if (str[0] == 'r')
		return (T_REG);
	else if (str[0] == DIRECT_CHAR)
		return (T_DIR);
	return (T_IND);
}

static int				ft_get_param_code(int num)
{
	if (num == T_REG)
		return (REG_CODE);
	else if (num == T_DIR)
		return (DIR_CODE);
	return (IND_CODE);
}

int				ft_get_ocp(t_instru *inst)
{
	int		i;
	if (ft_check_params_type(inst) == ERROR)
		return (ERROR);
	if (g_op_tab[inst->op_code - 1].nb_params > 1 || inst->op_code == 16)
	{
		i = -1;
		while (++i < 3)
		{
			if (i < g_op_tab[inst->op_code - 1].nb_params)
				inst->ocp += ft_get_param_code(ft_get_t_param(inst->params[i]));
			inst->ocp = inst->ocp << 2;
		}
	}
	return (SUCCESS);
}
