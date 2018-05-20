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

int				ft_get_params(t_instru *inst, char *str)
{
	int		i;
	char	*trim;

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
	free(trim);
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
			if (!(champ->instru = ft_lstnew(inst, sizeof(t_instru))))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(new = ft_lstnew(inst, sizeof(t_instru))))
				exit(EXIT_FAILURE);
			ft_lstaddend(&(champ->instru), new);
		}
		free(inst);
//		ft_free_struct_instru(inst);
		cur = cur->next;
	}
	return (SUCCESS);
}
