/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:49:20 by eparisot          #+#    #+#             */
/*   Updated: 2018/05/15 13:50:19 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_champ_name(char *line, t_champ *champ)
{
	while (*line != ' ' && *line != '\t')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	if (!(champ->name = ft_strdup(line)))
		return (0);
	ft_printf("NAME = %s\n", champ->name);
	return (1);
}

int		get_champ_com(char *line, t_champ *champ)
{
	while (*line != ' ' && *line != '\t')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	if (!(champ->comment = ft_strdup(line)))
		return (0);
	ft_printf("COMMENT = %s\n", champ->comment);
	return (1);
}

int		store_op(char *line, t_champ *chqmp)
{
	//TODO
	return (1);
}

int		parse_line(char *line, t_champ *champ)
{
	if (ft_strstr(line, ".name"))
	{
		if (!get_champ_name(line, champ))
			return (0);
	}
	else if (ft_strstr(line, ".comment"))
	{
		if (!get_champ_com(line, champ))
			return (0);
	}
	else
	{
		if (!store_op(line, champ))
			return (0);
	}
	return (1);
}

int		read_file(char *file_name, t_champ *champ)
{
	int		fd;
	char	**line;

	if (!(fd = open(file_name, O_RDONLY)))
		return (0);
	if (!(line = (char**)malloc(sizeof(char*))))
		return (0);
	while (get_next_line(fd, line) > 0)
	{
		if (!parse_line(*line, champ))
			return (0);
		free(*line);
	}
	free(line);
	close(fd);
	return (1);
}

void	del(void *content, size_t content_size)
{
	//TODO
}

void	del_champ(t_champ *champ)
{
	free(champ->name);
	free(champ->comment);
	ft_lstdel(&champ->instru, del);
	free(champ);
}

int		main(int ac, char **av)
{
	t_champ		*champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (0);
	if (ac > 1 && !read_file(av[1], champ))
	{
		free(champ);
		return (0);
	}
	del_champ(champ);
	return (1);
}
