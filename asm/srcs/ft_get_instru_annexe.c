/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instru_annexe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 19:20:59 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/21 18:36:36 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

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

int				ft_get_t_param(char *str)
{
	if (str[0] == 'r')
		return (T_REG);
	else if (str[0] == DIRECT_CHAR)
		return (T_DIR);
	else if (ft_strisdigit(str))
		return (T_IND);
	return (ERROR);
}

static int		ft_get_param_code(int num)
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
