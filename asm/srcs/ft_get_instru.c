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
//		ft_printf("{green}%s{eoc}\n", inst->label_name);
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

void			ft_clean_spaces_comments(t_instru *inst)
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
		if (ft_strchr(inst->params[i], COMMENT_CHAR))
		{
			while (inst->params[i][k] != COMMENT_CHAR)
				--k;
			while (inst->params[i][k] == COMMENT_CHAR)
				--k;
		}
		while (inst->params[i][k] == ' ' || inst->params[i][k] == '\t')
			--k;
		clean = ft_strndup(inst->params[i] + j, k - j + 1);
		free(inst->params[i]);
		inst->params[i] = clean;
	}
}

int				ft_check_params_format(t_instru *inst, char *str)
{
	int		nb_params;
	int		i;
	int		count_separators;

	nb_params = g_op_tab[inst->op_code - 1].nb_params;
	i = -1;
	count_separators = 0;
	while (str[++i])
	{
		if (str[i] == SEPARATOR_CHAR)
			++count_separators;
		else if (str[i] == COMMENT_CHAR && count_separators != nb_params - 1)
			return (ERROR);
	}
	if (count_separators == nb_params - 1)
		return (SUCCESS);
	return (ERROR);
}

int				ft_get_params(t_instru *inst, char *str)
{
	int		i;
	char	*trim;

//	ft_printf("%s\n", str);
	if (ft_check_params_format(inst, str) == ERROR)
		return (ERROR);
	str = ft_strstr(str, g_op_tab[inst->op_code - 1].name);
	i = -1;
	while (++i < (int)ft_strlen(g_op_tab[inst->op_code - 1].name))
		str++;
	if (*str == LABEL_CHAR)
	{
		str = ft_strstr(str, g_op_tab[inst->op_code - 1].name);
		i = -1;
		while (++i < (int)ft_strlen(g_op_tab[inst->op_code - 1].name))
			str++;
	}
	trim = ft_strtrim(str);
	inst->params = ft_malloc(sizeof(char *) * g_op_tab[inst->op_code - 1].nb_params, EXIT_FAILURE);
	inst->params = ft_strsplit(trim, SEPARATOR_CHAR);
	ft_clean_spaces_comments(inst);
//	int j = -1;
//	while (inst->params[++j])
//		ft_printf("{red}%s,{eoc}", inst->params[j]);
//	ft_printf("\n");
	free(trim);
	return (SUCCESS);
}

int				ft_check_ocp_addition(int total, int num)
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

int				ft_get_t_param(char *str)
{
	if (str[0] == 'r')
		return (T_REG);
	else if (str[0] == DIRECT_CHAR)
		return (T_DIR);
	return (T_IND);
}

int				ft_get_param_code(int num)
{
	if (num == T_REG)
		return (REG_CODE);
	else if (num == T_DIR)
		return (DIR_CODE);
	return (IND_CODE);
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
//		ft_printf("{red}%d\n{eoc}", g_op_tab[inst->op_code - 1].params_type[i]);
		if (ft_check_ocp_addition(g_op_tab[inst->op_code - 1].params_type[i], ft_get_t_param(inst->params[i])) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int				ft_get_ocp(t_instru *inst)
{
	int		i;
	if (ft_check_params_type(inst) == ERROR)
		return (ERROR);
//	inst->ocp = ft_get_param_code(ft_get_t_param(inst->params[0]));
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
			inst->size += (g_op_tab[inst->op_code - 1].direct_size == 1) ? 2 : 4;
	}
}

int				ft_fill_instru(t_instru *inst, char *str)
{
	if (ft_get_label_name(inst, str) == ERROR)
		return (ERROR);
	ft_get_op_code(inst, str);
//	ft_printf("%s\n{red}%d{eoc}\n", str, inst->op_code);
	if (inst->op_code != 0)
	{
		if (ft_get_params(inst, str) == ERROR)
			return (ERROR);
		if (ft_get_ocp(inst) == ERROR)
			return (ERROR);
		ft_get_size_instruction(inst);
//		ft_printf("%d\n", inst->size);
//		ft_printf("%.8b\n", (*inst)->ocp);
	}
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
		ft_printf("{green}%d\n{eoc}", (int)inst->op_code);
//		ft_printf("{red}%d\n{eoc}", (t_instru *)(champ->instru->content)->op_code);
		free(inst);
		cur = cur->next;
	}
	return (SUCCESS);
}
