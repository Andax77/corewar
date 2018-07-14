/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 14:47:51 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/11 18:21:33 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		check_last(char *add, char **text, int size, t_list *input)
{
	if (size % 4 == 3)
	{
		if (!(add = ft_itoa_base(ft_atoi(input->content) >> 8 & 16777215, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 6)
			pad(&add, 6);
	}
	else if (size % 4 == 2)
	{
		if (!(add = ft_itoa_base(ft_atoi(input->content) >> 16 & 65535, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 4)
			pad(&add, 4);
	}
	else if (size % 4 == 1)
	{
		if (!(add = ft_itoa_base(ft_atoi(input->content) >> 24 & 255, 16)))
			exit(EXIT_FAILURE);
		if (ft_strlen(add) < 2)
			pad(&add, 2);
	}
	ft_strcat(*text, add);
	ft_fruit(1, &add);
	(*text)[size * 2] = '\0';
	return (SUCCESS);
}

static int		check_prog_len(t_list *input, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	add = NULL;
	if (!(*text = ft_strnew(size * 2 + 1)))
		exit(EXIT_FAILURE);
	while (input && (i += 4))
	{
		if (i > size && (size % 4) != 0
				&& check_last(add, text, size, input) == SUCCESS)
			break ;
		else
		{
			if (!(add = ft_itoa_base(ft_atoi(input->content), 16)))
				exit(EXIT_FAILURE);
			if (ft_strlen(add) < 8)
				pad(&add, 8);
			ft_strcat(*text, add) && ft_fruit(1, &add);
		}
		input = input->next;
	}
	if (i != ((size % 4 == 0) ? size : size + 4 - size % 4))
		return (ERROR);
	return (SUCCESS);
}

static t_list	*check_len(t_list *input, int size, char **text)
{
	int		i;
	char	*add;

	i = 0;
	if (!(*text = ft_strnew(size + 1)))
		exit(EXIT_FAILURE);
	while (input && i < size)
	{
		if (ft_atoi(input->content) != 0)
		{
			if (!(add = translate(ft_atoi(input->content))))
				exit(EXIT_FAILURE);
			ft_strcat(*text, add);
			free(add);
		}
		input = input->next;
		i += 4;
	}
	if (!input || ft_atoi(input->content) != 0)
		return (NULL);
	return (input);
}

static int		ft_check_champ_binary_bis(t_list *input, t_champ **champ)
{
	int				inst_length;
	char			*prog;
	unsigned char	*splitted_prog;

	prog = NULL;
	splitted_prog = NULL;
	if ((inst_length = ft_atoi(input->content)) > CHAMP_MAX_SIZE)
		return (ft_error(*champ, "instructions length too big"));
	if (!(input = check_len(input->next, COMMENT_LENGTH, &(*champ)->comment)))
		return (ft_error(*champ, "has wrong comment length"));
	if (check_prog_len(input->next, inst_length, &prog) == ERROR)
	{
		free(prog);
		return (ft_error(*champ, "instructions length is incorrect"));
	}
	splitted_prog = split_bits(prog);
	free(prog);
	if (ft_decrypt_prog(*champ, splitted_prog, inst_length) == ERROR)
	{
		free(splitted_prog);
		return (ERROR);
	}
	free(splitted_prog);
	return (SUCCESS);
}

int				ft_check_champ_binary(t_champ **champ)
{
	t_list	*input;

	if (!(input = (*champ)->input))
		return (ft_error(*champ, "is empty"));
	if (ft_atoi(input->content) != COREWAR_EXEC_MAGIC)
		return (ft_error(*champ, "has wrong CEM"));
	if (PROG_NAME_LENGTH % 4 != 0 || COMMENT_LENGTH % 4 != 0)
		return (ft_error(*champ, "please stop touching op.h !"));
	if (!(input = check_len(input->next, PROG_NAME_LENGTH, &(*champ)->name)))
		return (ft_error(*champ, "has wrong name length"));
	if (ft_check_champ_binary_bis(input->next, champ) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
