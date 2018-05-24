/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor_annexe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:05:26 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/24 22:30:26 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int			ft_fill_file_name(t_champ *champ, char *name)
{
	int		i;
	int		marqueur;

	i = -1;
	marqueur = 0;
	while (name[++i])
	{
		if (name[i] == '.')
			marqueur = i;
	}
	if (i == 0 || marqueur == 0 || name[marqueur + 1] != 's')
		return (ft_error(champ, "error: wrong file format <sourcefile.s>"));
	if (!(champ->file_name = ft_strndup(name, marqueur)))
		exit(EXIT_FAILURE);
	if (!(champ->file_name = ft_str_and_free_join(champ->file_name, ".cor")))
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

static int	ft_get_octets_params(t_instru *cur, int i)
{
	if (ft_get_t_param(cur->params[i]) == T_REG)
		return (1);
	else if (ft_get_t_param(cur->params[i]) == T_IND)
		return (2);
	else
	{
		if (g_op_tab[cur->op_code - 1].dir_size == 1)
			return (2);
		else
			return (4);
	}
}

int			ft_fill_output_params(t_instru *cur, char *output, int cursor)
{
	char	*write;
	int		i;
	int		octets;
	int		decalage;

	i = -1;
	while (cur->params[++i])
	{
		octets = ft_get_octets_params(cur, i);
		decalage = (ft_get_t_param(cur->params[i]) == T_DIR) ? 1 : 0;
		write = ft_malloc(octets, EXIT_FAILURE);
		if (octets == 4)
			*(int *)write = swap_int32(ft_atoi(cur->params[i] + decalage));
		else if (octets == 2)
			*(short *)write = swap_int16(ft_atoi(cur->params[i] + decalage));
		else
			*(char *)write = ft_atoi(cur->params[i] + 1);
		ft_memcpy(output + cursor, write, octets);
		cursor += octets;
		free(write);
	}
	return (cursor);
}
