/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 00:43:44 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 18:39:38 by pmilan           ###   ########.fr       */
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

static void	ft_fill_output_instructions(t_champ *champ, char *output,
		int cursor)
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

static void	ft_fill_output(t_champ *champ, char *output, int instructions_len)
{
	char	*tmp;
	int		cursor;

	tmp = ft_malloc(sizeof(COREWAR_EXEC_MAGIC), EXIT_FAILURE);
	if (sizeof(COREWAR_EXEC_MAGIC) == 4)
		*(int *)tmp = swap_int32(COREWAR_EXEC_MAGIC);
	ft_memcpy(output, tmp, sizeof(COREWAR_EXEC_MAGIC));
	free(tmp);
	cursor = sizeof(COREWAR_EXEC_MAGIC);
	ft_memcpy(output + cursor, champ->name, ft_strlen(champ->name));
	cursor += PROG_NAME_LENGTH + 4;
	tmp = ft_malloc(sizeof(instructions_len), EXIT_FAILURE);
	if (sizeof(instructions_len == 4))
		*(int *)tmp = swap_int32(instructions_len);
	ft_memcpy(output + cursor, tmp, sizeof(instructions_len));
	free(tmp);
	cursor += sizeof(instructions_len);
	ft_memcpy(output + cursor, champ->comment, ft_strlen(champ->comment));
	cursor += COMMENT_LENGTH + 4;
	ft_fill_output_instructions(champ, output, cursor);
}

int			ft_write_cor(t_champ *champ)
{
	char	*output;
	int		len_output;
	int		instructions_len;
	int		fd;

	instructions_len = ft_get_instructions_length(champ);
	if (instructions_len > CHAMP_MAX_SIZE)
		return (ft_error(champ, "error: too many instructions"));
	if (sizeof(COREWAR_EXEC_MAGIC) > 4)
		return (ft_error(champ, "error: magic number is not an integer"));
	len_output = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 4
		+ sizeof(instructions_len) + COMMENT_LENGTH + 4 + instructions_len;
	output = ft_malloc(sizeof(char) * (len_output + 1), EXIT_FAILURE);
	ft_bzero(output, len_output + 1);
	ft_fill_output(champ, output, instructions_len);
	if ((fd = open(champ->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) <= 0)
		exit(EXIT_FAILURE);
	write(fd, output, len_output);
	ft_printf("{yellow}Writing output program to %s{eoc}\n", champ->file_name);
	free(output);
	return (SUCCESS);
}
