/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_instru.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:08:11 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 16:24:17 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

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

static char		*ft_get_name_op_code(t_instru *inst, char *str)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = NULL;
	i = -1;
	while (str[++i] && (str[i] == ' ' || str[i] == '\t'))
		;
	if (inst->label_name)
	{
		j = -1;
		while (str[i] == inst->label_name[++j])
			++i;
		while (str[++i] && (str[i] == ' ' || str[i] == '\t'))
			;
	}
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		++j;
	if (!(ptr = ft_strndup(str + i, j - i)))
		exit(EXIT_FAILURE);
	return (ptr);
}

int				ft_get_op_code(t_instru *inst, char *str)
{
	int		i;
	char	*ptr;

	i = -1;
	ptr = ft_get_name_op_code(inst, str);
	while (g_op_tab[++i].name)
	{
		if (strcmp(ptr, g_op_tab[i].name) == 0)
		{
			inst->op_code = g_op_tab[i].op_code;
			free(ptr);
			return (SUCCESS);
		}
	}
	free(ptr);
	return (ERROR);
}

int				ft_get_label_name(t_instru *inst, char *str)
{
	int		i;

	if (ft_strchr(str, LABEL_CHAR))
	{
		i = -1;
		while (str[++i] && str[i] != LABEL_CHAR)
			;
		if (i == 0)
			return (ERROR);
		if (str[i - 1] == DIRECT_CHAR)
			return (SUCCESS);
		if (!(inst->label_name = ft_strndup(str, i)))
			exit(EXIT_FAILURE);
		i = -1;
		while (inst->label_name[++i])
			if (!ft_strchr(LABEL_CHARS, inst->label_name[i]))
				return (ERROR);
	}
	return (SUCCESS);
}

int				ft_fill_instru(t_instru *inst, char *str)
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
