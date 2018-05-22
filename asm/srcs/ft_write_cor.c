/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 00:43:44 by pierremilan       #+#    #+#             */
/*   Updated: 2018/05/21 20:51:04 by pmilan           ###   ########.fr       */
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

static int	ft_fill_output_params(t_instru *cur, char *output, int cursor)
{
	int		i;
	char	*write;

	i = -1;
	while (cur->params[++i])//essayer de reduire en avancant pointeur cur->params[i] et faire un int octet
	{
		if (ft_get_t_param(cur->params[i]) == T_REG)
		{
			write = ft_malloc(1, EXIT_FAILURE);
			*(char *)write = ft_atoi(cur->params[i] + 1);
			ft_memcpy(output + cursor, write, 1);
			cursor += 1;
		}
		else if (ft_get_t_param(cur->params[i]) == T_IND)
		{
			write = ft_malloc(2, EXIT_FAILURE);
			*(short *)write = swap_int16(ft_atoi(cur->params[i]));
			ft_memcpy(output + cursor, write, 2);
			cursor += 2;
		}
		else
		{
			if (g_op_tab[cur->op_code - 1].direct_size == 1)
			{
				write = ft_malloc(2, EXIT_FAILURE);
				*(short *)write = swap_int16(ft_atoi(cur->params[i] + 1));
				ft_memcpy(output + cursor, write, 2);
				cursor += 2;
			}
			else
			{
				write = ft_malloc(4, EXIT_FAILURE);
				*(int *)write = swap_int32(ft_atoi(cur->params[i] + 1));
				ft_memcpy(output + cursor, write, 4);
				cursor += 4;
			}
		}
		free(write);
	}
	return (cursor);
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
			ft_memcpy(output + cursor, write, 1);
			free(write);
			cursor += 1;
			if (cur->ocp != 0)
			{
				write = ft_malloc(1, EXIT_FAILURE);
				*(char *)write = (char)cur->ocp;
				ft_memcpy(output + cursor, write, 1);
				free(write);
				cursor += 1;
			}
			if (cur->params)
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
	int		length_output;
	int		instructions_length;
	int		s;

	(void)name;
	instructions_length = ft_get_instructions_length(champ);
//	ft_printf("{magenta}%d\n{yellow}%d\n{eoc}", instructions_length, sizeof(instructions_length));
	length_output = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 4 + sizeof(instructions_length) + COMMENT_LENGTH + 4 + instructions_length;
//	ft_printf("{yellow}%d\n{eoc}", length_output);
	output = ft_malloc(sizeof(char) * (length_output + 1), EXIT_FAILURE);
	ft_bzero(output, length_output + 1);
	ft_fill_output(champ, output, instructions_length);
//	ft_printf("{red}%r{eoc}\n", output, 2215);
	s = open("serge", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	write(s, output, 2215);
	free(output);
}
