/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:34:36 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/22 16:21:12 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	store_lines(t_champ *champ)
{
	char	*line;
	t_list	*new;

	line = NULL;
	new = NULL;
	while (get_next_line(champ->fd, &line) == GNL_SUCCESS)
	{
		if (!champ->input)
		{
			if (!(champ->input = ft_lstnew(line, ft_strlen(line) + 1)))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(new = ft_lstnew(line, ft_strlen(line) + 1)))
				exit(EXIT_FAILURE);
			ft_lstaddend(&champ->input, new);
		}
		free(line);
	}
}

int			read_file(char *file_name, t_champ *champ)
{
	int		stock;
	char	*line;

	if (!(champ->fd = open(file_name, O_RDONLY)))
		return (ERROR);
	line = NULL;
	stock = UNFINISHED;
	while (get_next_line(champ->fd, &line) == GNL_SUCCESS)
	{
		stock = parse_line(line, champ);
		free(line);
		if (stock == FINISHED)
			break ;
	}
	store_lines(champ);
	if (ft_get_instru(champ) == ERROR)
		ft_error(champ, "error: instruction problem");// voir a personnaliser ca
	ft_fill_inst_addr(champ);
	ft_replace_direct(champ);
	close(champ->fd);
	return (SUCCESS);
}
