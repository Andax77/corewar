/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremilan <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 21:38:34 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/10 17:41:46 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	ft_fill_output_prog_params_binary(t_instru *cur, char **output)
{
	int		i;

	i = -1;
	while (cur->params[++i])
	{
		if (!(*output = ft_str_and_free_join(*output, cur->params[i])))
			exit(EXIT_FAILURE);
		if (cur->params[i + 1])
		{
			if (!(*output = ft_str_and_free_join(*output, ", ")))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(*output = ft_str_and_free_join(*output, "\n")))
				exit(EXIT_FAILURE);
		}
	}
}

static void	ft_fill_output_prog_binary(t_champ *champ, char **output)
{
	t_list		*tmp;
	t_instru	*cur;

	tmp = champ->instru;
	while (tmp != NULL)
	{
		cur = (t_instru *)tmp->content;
		if (!(*output = ft_str_and_free_join(*output,
											g_op_tab[cur->op_code - 1].name)))
			exit(EXIT_FAILURE);
		if (!(*output = ft_str_and_free_join(*output, " ")))
			exit(EXIT_FAILURE);
		ft_fill_output_prog_params_binary(cur, output);
		tmp = tmp->next;
	}
}

static void	ft_fill_output_binary(t_champ *champ, char **output)
{
	if (!(*output = ft_str_and_free_join(*output, NAME_CMD_STRING)))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, " \"")))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, champ->name)))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, "\"\n")))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, COMMENT_CMD_STRING)))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, " \"")))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, champ->comment)))
		exit(EXIT_FAILURE);
	if (!(*output = ft_str_and_free_join(*output, "\"\n\n")))
		exit(EXIT_FAILURE);
	ft_fill_output_prog_binary(champ, output);
}

int			ft_write_s(t_champ *champ)
{
	char	*output;
	int		fd;

	if (!(output = ft_strnew(1)))
		exit(EXIT_FAILURE);
	ft_fill_output_binary(champ, &output);
	if ((fd = open(champ->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) <= 0)
		exit(EXIT_FAILURE);
	write(fd, output, ft_strlen(output));
	ft_printf("{yellow}Writing output program to %s{eoc}\n", champ->file_name);
	free(output);
	return (SUCCESS);
}
