/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:22:52 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/10 17:39:46 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		ft_check_ocp_addition(int total, int num)
{
	if (total == 1 && num != 1)
		return (ERROR);
	else if (total == 2 && num != 2)
		return (ERROR);
	else if (total == 3 && !(num == 1 || num == 2))
		return (ERROR);
	else if (total == 5 && !(num == 1 || num == 4))
		return (ERROR);
	else if (total == 6 && !(num == 2 || num == 4))
		return (ERROR);
	else if (total == 7 && !(num == 1 || num == 2 || num == 4))
		return (ERROR);
	return (SUCCESS);
}

int				ft_check_params_type(t_instru *inst)
{
	int		i;

	i = -1;
	while (inst->params[++i])
		;
	if (i != g_op_tab[inst->op_code - 1].nb_params)
		return (ERROR);
	i = -1;
	while (inst->params[++i])
	{
		if (ft_get_t_param(inst->params[i]) == ERROR || \
ft_check_ocp_addition(g_op_tab[inst->op_code - 1].params_type[i], \
ft_get_t_param(inst->params[i])) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int				ft_check_params_format(t_instru *inst, char *str)
{
	int		nb_params;
	int		i;
	int		count_separators;

	nb_params = g_op_tab[inst->op_code - 1].nb_params;
	i = -1;
	count_separators = 0;
	while (str[++i] && str[i] != COMMENT_CHAR)
		if (str[i] == SEPARATOR_CHAR)
			++count_separators;
	if (count_separators == nb_params - 1)
		return (SUCCESS);
	return (ERROR);
}

int				ft_check_input_format(t_champ *champ)
{
	t_list		*tmp;
	char		*str;
	int			i;

	if (champ->name == NULL)
		return (ft_error(champ, "error: no program name found"));
	if (champ->comment == NULL)
		return (ft_error(champ, "error: no comment found"));
	tmp = champ->input;
	while ((i = -1) && tmp != NULL)
	{
		str = (char *)tmp->content;
		while (str[++i] && (str[i] == ' ' || str[i] == '\t'))
			;
		if (str[i] && str[i] == '.')
		{
			if (ft_strcmp(str + i, NAME_CMD_STRING) == 0)
				return (ft_error(champ, "error: several names of file found"));
			else if (ft_strcmp(str + i, COMMENT_CMD_STRING) == 0)
				return (ft_error(champ, "error: several comments found"));
			return (ft_error(champ, "error: unknown command found"));
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int				ft_empty_or_comment_line(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR)
			return (EMPTY);
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && \
str[i] != '\v' && str[i] != '\n' && str[i] != '\f')
			return (CHARACTER);
	}
	return (EMPTY);
}
