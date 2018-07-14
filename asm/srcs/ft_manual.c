/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 20:20:15 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 18:31:44 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	ft_fill_output_m(t_champ *champ, char *output, char *f_instructions,
		int instructions_len)
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
	ft_memcpy(output + cursor, f_instructions, instructions_len);
}

static int	ft_fill_instructions_next_m(t_champ *champ, char *instructions,
		char **f_instructions, int *instructions_length)
{
	int		i;
	char	*sub;

	i = -1;
	while (instructions[++i])
		if (!ft_strchr(BASE_HEXA, instructions[i]))
		{
			free(instructions);
			return (ft_error_m(champ, "error: instruction larger than 0xF"));
		}
	*f_instructions = ft_strnew(*instructions_length + 1);
	i = 0;
	while (instructions[i])
	{
		if (!(sub = ft_strsub(instructions, i, 2)))
			exit(EXIT_FAILURE);
		(*f_instructions)[i / 2] = (char)ft_atoi_base(sub, 16);
		free(sub);
		i += 2;
	}
	free(instructions);
	return (SUCCESS);
}

static int	ft_fill_instructions_m(t_champ *champ, char **f_instructions,
		int *instructions_length)
{
	char	*instructions;

	instructions = NULL;
	ft_printf("{yellow}What is the champion's code ?{eoc}\n");
	if (get_next_line(STDIN_FILENO, &instructions) != GNL_SUCCESS)
		return (ft_error_m(champ, "error: oups something went wrong..."));
	if (ft_strlen(instructions) % 2 == 1)
	{
		free(instructions);
		return (ft_error_m(champ, "error: odd length of instructions"));
	}
	ft_str_toupper(instructions);
	*instructions_length = ft_strlen(instructions) / 2;
	if (ft_fill_instructions_next_m(champ, instructions, f_instructions,
				instructions_length) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	ft_write_cor_m(t_champ *champ, int instructions_len,
		char *f_instructions)
{
	char	*output;
	int		length_output;
	int		fd;

	length_output = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 4
		+ sizeof(instructions_len) + COMMENT_LENGTH + 4 + instructions_len;
	output = ft_malloc(sizeof(char) * (length_output + 1), EXIT_FAILURE);
	ft_fill_output_m(champ, output, f_instructions, instructions_len);
	ft_printf("{yellow}What is the name of the program (please finish the name \
		with '.cor') ?{eoc}\n");
	ft_fruit(1, &champ->file_name);
	if (get_next_line(STDIN_FILENO, &champ->file_name) != GNL_SUCCESS
			&& ft_fruit(1, &output))
		return (ft_error_m(champ, "error: oups something went wrong..."));
	if (champ->file_name[0] == '\0' || ft_strchr(champ->file_name, '/'))
	{
		ft_fruit(1, &output);
		return (ft_error_m(champ, "error: oups something went wrong..."));
	}
	if ((fd = open(champ->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) <= 0)
		exit(EXIT_FAILURE);
	write(fd, output, length_output);
	ft_printf("{yellow}Writing output program to %s{eoc}\n", champ->file_name);
	free(output);
	return (SUCCESS);
}

int			ft_manual(t_champ *champ)
{
	char	*inst;
	int		inst_len;

	inst = NULL;
	inst_len = 0;
	ft_printf("{yellow}What is the champion's name ?{eoc}\n");
	if (get_next_line(STDIN_FILENO, &champ->name) != GNL_SUCCESS)
		return (ft_error_m(champ, "error: oups something went wrong..."));
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return (ft_error_m(champ, "error: champion's name is too long"));
	ft_printf("{yellow}What is the comment ?{eoc}\n");
	if (get_next_line(STDIN_FILENO, &champ->comment) != GNL_SUCCESS)
		return (ft_error_m(champ, "error: oups something went wrong..."));
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		return (ft_error_m(champ, "error: comment is too long"));
	if (ft_fill_instructions_m(champ, &inst, &inst_len) == ERROR)
		return (ERROR);
	if (ft_write_cor_m(champ, inst_len, inst) == ERROR && ft_fruit(1, &inst))
		return (ERROR);
	del_champ(champ);
	ft_printf("{yellow}Please press ^d{eoc}\n") && ft_fruit(1, &inst);
	while (get_next_line(STDIN_FILENO, &inst) != GNL_END)
		ft_printf("{yellow}Please press ^d{eoc}\n") && ft_fruit(1, &inst);
	free(inst);
	return (SUCCESS);
}
