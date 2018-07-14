/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 23:28:10 by eparisot          #+#    #+#             */
/*   Updated: 2018/07/14 10:24:11 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static t_list	*check_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size + 1)))
		exit(EXIT_FAILURE);
	while (instru && i < size)
	{
		if (ft_atoi(instru->content) != 0)
		{
			if (!(add = translate(ft_atoi(instru->content))))
				exit(EXIT_FAILURE);
			ft_strcat(*text, add);
			free(add);
		}
		instru = instru->next;
		i += 4;
	}
	if (!instru || ft_atoi(instru->content) != 0)
		return (NULL);
	return (instru);
}

static int		check_last(char *add, char **text, int size, t_list *instru)
{
	if (size % 4 == 3)
	{
		if (!(add = ft_itoa_base(ft_atoi(instru->content) >> 8 & 16777215, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 6)
			pad(&add, 6);
	}
	else if (size % 4 == 2)
	{
		if (!(add = ft_itoa_base(ft_atoi(instru->content) >> 16 & 65535, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 4)
			pad(&add, 4);
	}
	else if (size % 4 == 1)
	{
		if (!(add = ft_itoa_base(ft_atoi(instru->content) >> 24 & 255, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 2)
			pad(&add, 2);
	}
	ft_strcat(*text, add);
	ft_fruit(1, &add);
	(*text)[size * 2] = '\0';
	return (SUCCESS);
}

static int		check_prog_len(t_list *instru, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	add = NULL;
	if (!(*text = ft_strnew(size * 2 + 1)))
		exit(EXIT_FAILURE);
	while (instru && (i += 4))
	{
		if (i > size && (size % 4) != 0 && check_last(add, text, size, instru))
			break ;
		else
		{
			if (!(add = ft_itoa_base(ft_atoi(instru->content), 16)))
				exit(EXIT_FAILURE);
			if (ft_strlen(add) < 8)
				pad(&add, 8);
			ft_strcat(*text, add);
			ft_fruit(1, &add);
		}
		instru = instru->next;
	}
	if (i != ((size % 4 == 0) ? size : size + 4 - size % 4))
		return (ERROR);
	return (SUCCESS);
}

static int		check_champ_bis(t_list *instru, t_champ **champ, char *path)
{
	if (((*champ)->op_nb = ft_atoi(instru->content)) > CHAMP_MAX_SIZE)
		return (ft_print_error("has wrong length", path));
	if (!(instru = check_len(instru->next, COMMENT_LENGTH, &(*champ)->comment)))
		return (ft_print_error("has wrong comment length", path));
	if (check_prog_len(instru->next, (*champ)->op_nb, &(*champ)->prog) == ERROR)
		return (ft_print_error("has wrong length", path));
	split_bits(&(*champ)->prog, &(*champ)->splited_prog);
	if (check_op_len(*champ) == ERROR)
		return (ft_print_error("invalid operation", path));
	return (SUCCESS);
}

int				check_champ(t_champ **champ, char *path, int nb)
{
	t_list		*instru;
	static int	id;

	if (!(instru = (*champ)->instru))
		return (ft_print_error("is empty", path));
	if (ft_atoi(instru->content) != COREWAR_EXEC_MAGIC)
		return (ft_print_error("has wrong CEM", path));
	if (PROG_NAME_LENGTH % 4 != 0 || COMMENT_LENGTH % 4 != 0)
		return (ft_print_error("stop touching op.h !", NULL));
	if (!(instru = check_len(instru->next, PROG_NAME_LENGTH, &(*champ)->name)))
		return (ft_print_error("has wrong name length", path));
	if (check_champ_bis(instru->next, champ, path) == ERROR)
		return (ERROR);
	(*champ)->reg = ft_malloc(REG_NUMBER * REG_SIZE, EXIT_FAILURE);
	(*champ)->reg[0] = nb;
	(*champ)->id = ++id;
	(*champ)->v_id = nb;
	return (SUCCESS);
}
