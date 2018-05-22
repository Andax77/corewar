/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 00:43:44 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/22 15:11:18 by pmilan           ###   ########.fr       */
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
	ret = cur->inst_addr + cur->size;
	return (ret);
}

static void	ft_fill_output_instructions(t_champ *champ, char *output, int cursor)
{
	t_list		*tmp;
	t_instru	*cur;
	char		*write;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if (cur->op_code != 0)
		{
			write = ft_malloc(1, EXIT_FAILURE);
			*(char *)write = (char)cur->op_code;
			ft_memcpy(output + cursor++, write, 1);
			free(write);
			if (cur->ocp != 0)
			{
				write = ft_malloc(1, EXIT_FAILURE);
				*(char *)write = (char)cur->ocp;
				ft_memcpy(output + cursor++, write, 1);
				free(write);
			}
			cursor = ft_fill_output_params(cur, output, cursor);
		}
		tmp = tmp->next;
	}
}

static void	ft_fill_output(t_champ *champ, char *output, int instructions_length)
{
	char	*tmp;
	int		cursor;

	tmp = ft_malloc(sizeof(COREWAR_EXEC_MAGIC), EXIT_FAILURE);
	*(int *)tmp = swap_int32(COREWAR_EXEC_MAGIC);
	ft_memcpy(output, tmp, sizeof(COREWAR_EXEC_MAGIC));
	free(tmp);
	cursor = sizeof(COREWAR_EXEC_MAGIC);
	ft_memcpy(output + cursor, champ->name, ft_strlen(champ->name));
	cursor += PROG_NAME_LENGTH + 4;
	tmp = ft_malloc(sizeof(instructions_length), EXIT_FAILURE);
	*(int *)tmp = swap_int32(instructions_length);//verif que int 32 suffit
	ft_memcpy(output + cursor, tmp, sizeof(instructions_length));
	free(tmp);
	cursor += sizeof(instructions_length);
	ft_memcpy(output + cursor, champ->comment, ft_strlen(champ->comment));
	cursor += COMMENT_LENGTH + 4;
	ft_fill_output_instructions(champ, output, cursor);
}

void		ft_write_cor(t_champ *champ, char *name)
{
	char	*output;
	char	*file_name;
	int		length_output;
	int		instructions_length;
	int		s;

	file_name = NULL;
	if (ft_fill_file_name(name, &file_name) == ERROR)
	{
		ft_fruit(1, &file_name);
		ft_error(champ, "mauvais format de fichier");
	}
	instructions_length = ft_get_instructions_length(champ);
	length_output = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 4 +
		sizeof(instructions_length) + COMMENT_LENGTH + 4 + instructions_length;
	output = ft_malloc(sizeof(char) * (length_output + 1), EXIT_FAILURE);
	ft_bzero(output, length_output + 1);
	ft_fill_output(champ, output, instructions_length);
	if (!(s = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)))
		exit(EXIT_FAILURE);
	write(s, output, length_output);
	free(file_name);
	free(output);
}
