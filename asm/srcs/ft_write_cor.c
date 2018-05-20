/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 00:43:44 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/21 00:43:44 by pierremilan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	ft_get_instructions_length(t_champ *champ)
{
	t_list		*tmp;
	t_instru	*cur;
	int			ret;

	tmp = champ->instru;
	while (tmp->next != NULL)
		tmp = tmp->next;
	cur = (t_instru *)tmp->content;
	ret = cur->label_addr + cur->size;
	return (ret);
}

void		ft_write_cor(t_champ *champ, char *name)
{
	char	*output;
	int		length_output;
	int		instructions_length;

	instructions_length = ft_get_instructions_length(champ);
	ft_printf("{magenta}%d\n{yellow}%d\n{eoc}", instructions_length, sizeof(instructions_length));
	length_output = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(COREWAR_EXEC_MAGIC) + sizeof(instructions_length) + 8;
	ft_printf("{yellow}%d\n{eoc}", length_output);
	output = ft_malloc(sizeof(char) * (length_output + 1), EXIT_FAILURE);
	ft_bzero(output, length_output + 1);
}
