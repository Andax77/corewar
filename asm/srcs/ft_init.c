/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:33:26 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/29 17:48:23 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		ft_init_champ(t_champ *champ, char *argv)
{
	if (!(champ->argv = ft_strdup(argv)))
		exit(EXIT_FAILURE);
	champ->file_name = NULL;
	champ->name = NULL;
	champ->comment = NULL;
	champ->input = NULL;
	champ->instru = NULL;
	champ->fd = -1;
}

t_instru	*ft_init_instru(void)
{
	t_instru	*inst;

	inst = ft_malloc(sizeof(t_instru), EXIT_FAILURE);
	inst->params = NULL;
	inst->label_name = NULL;
	inst->op_code = 0;
	inst->ocp = 0;
	inst->size = 0;
	inst->inst_addr = 0;
	return (inst);
}

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

int			ft_fill_binary_name(t_champ *champ, char *name)
{
	int		i;
	int		marqueur;

	i = -1;
	marqueur = 0;
	if (!(ft_strstr(name, ".cor")))
		return (ft_error(champ, "error: wrong file format <sourcefile.cor>"));
	while (name[++i])
	{
		if (name[i] == '.')
			marqueur = i;
	}
	if (!(champ->file_name = ft_strndup(name, marqueur)))
		exit(EXIT_FAILURE);
	if (!(champ->file_name = ft_str_and_free_join(champ->file_name, ".s")))
		exit(EXIT_FAILURE);
	return (SUCCESS);
}
