/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decrypt_prog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:05:18 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/12 17:09:37 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			ft_fill_params_binary(t_champ *champ, t_instru *inst,
													unsigned char *prog, int *i)
{
	int		j;
	int		tmp;
	char	*tmp_num;

	j = -1;
	while (!(tmp = 0) && inst->params[++j])
	{
		if (inst->params[j][0] == DIRECT_CHAR)
		{
			if (g_op_tab[inst->op_code - 1].dir_size == 0)
				tmp = (prog[(*i)++] << 24) + (prog[(*i)++] << 16);
			tmp += (prog[(*i)++] << 8) + prog[(*i)++];
		}
		else if (inst->params[j][0] == '\0')
			tmp = (prog[(*i)++] << 8) + prog[(*i)++];
		else if (inst->params[j][0] == 'r')
			if (!(tmp = prog[(*i)++]) && (tmp > REG_NUMBER || tmp < 1))
				return (ft_error(champ, "wrong reg number"));
		if ((!(tmp_num = ft_itoa(tmp))) || \
(!(inst->params[j] = ft_str_and_free_join(inst->params[j], tmp_num))))
			exit(EXIT_FAILURE);
		free(tmp_num);
	}
	return (SUCCESS);
}

static void	ft_malloc_params_binary(char **params, int tmp_ocp)
{
	if (tmp_ocp == 1)
	{
		if (!(*params = ft_strdup("r")))
			exit(EXIT_FAILURE);
	}
	else if (tmp_ocp == 2)
	{
		if (!(*params = ft_strnew(2)))
			exit(EXIT_FAILURE);
		(*params)[0] = DIRECT_CHAR;
	}
	else
	{
		if (!(*params = ft_strnew(1)))
			exit(EXIT_FAILURE);
	}
}

int			ft_fill_ocp_binary(t_champ *champ, t_instru *inst,
													unsigned char *prog, int *i)
{
	int		j;
	int		tmp_ocp;

	inst->ocp = prog[(*i)++];
	j = -1;
	inst->params = ft_malloc(sizeof(char *) * \
(g_op_tab[inst->op_code - 1].nb_params + 1), EXIT_FAILURE);
	inst->params[g_op_tab[inst->op_code - 1].nb_params] = 0;
	while (++j < g_op_tab[inst->op_code - 1].nb_params)
	{
		tmp_ocp = (((inst->ocp >> (2 * (3 - j))) & 0x3) == 3) ? 4 : \
(inst->ocp >> (2 * (3 - j))) & 0x3;
		if ((tmp_ocp & (g_op_tab[inst->op_code - 1].params_type[j])) != tmp_ocp)
			return (ft_error(champ, "wrong ocp"));
		ft_malloc_params_binary(&inst->params[j], tmp_ocp);
	}
	return (SUCCESS);
}

int			ft_fill_instru_binary(t_champ *champ, t_instru *inst,
													unsigned char *prog, int *i)
{
	if (prog[*i] > 16 || prog[*i] < 1)
		return (ft_error(champ, "wrong op_code"));
	inst->op_code = prog[(*i)++];
	if (g_op_tab[inst->op_code - 1].ocp == 1)
	{
		if (ft_fill_ocp_binary(champ, inst, prog, i) == ERROR)
			return (ERROR);
	}
	else
	{
		inst->params = ft_malloc(sizeof(char *) * 2, EXIT_FAILURE);
		inst->params[1] = 0;
		if (!(inst->params[0] = ft_strnew(2)))
			exit(EXIT_FAILURE);
		inst->params[0][0] = DIRECT_CHAR;
	}
	if (ft_fill_params_binary(champ, inst, prog, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int			ft_decrypt_prog(t_champ *champ, unsigned char *prog,
																int inst_length)
{
	int			i;
	t_instru	*inst;

	i = 0;
	while (i < inst_length)
	{
		inst = ft_init_instru();
		if (ft_fill_instru_binary(champ, inst, prog, &i) == ERROR)
		{
			ft_free_struct_instru(inst);
			return (ERROR);
		}
		ft_fill_lst_instru(champ, inst);
		free(inst);
	}
	return (SUCCESS);
}
