/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:34:36 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/23 12:00:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	ft_check_input_format(t_champ *champ)
{
	t_list		*tmp;
	char		*str;
	int			i;

	if (champ->name == NULL)
		ft_error(champ, "error: no program name found");
	if (champ->comment == NULL)
		ft_error(champ, "error: no comment found");
	tmp = champ->input;
	while ((i = -1) && tmp != NULL)
	{
		str = (char *)tmp->content;
		while (str[++i] && (str[i] == ' ' || str[i] == '\t'))
			;
		if (str[i] && str[i] == '.')
		{
			if (ft_strncmp(str + i, ".name", 5) == 0)
				ft_error(champ, "error: several names of file found");
			else if (ft_strncmp(str + i, ".comment", 8) == 0)
				ft_error(champ, "error: several comments found");
			else
				ft_error(champ, "error: unknown command found");
		}
		tmp = tmp->next;
	}
}

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
	char	*line;
	int		stock;
	int		result_gnl;

	if ((champ->fd = open(file_name, O_RDONLY)) <= 0)
		return (ERROR);
	line = NULL;
	stock = UNFINISHED;
	while ((result_gnl = get_next_line(champ->fd, &line)) == GNL_SUCCESS)
	{
		stock = parse_line(line, champ);
		free(line);
		if (stock == FINISHED)
			break ;
	}
	if (result_gnl == GNL_ERROR)
		ft_error(champ, "error: bad file descriptor");
	store_lines(champ);
	close(champ->fd);
	ft_check_input_format(champ);
	if (ft_get_instru(champ) == ERROR)
		ft_error(champ, "error: instruction problem");// voir a personnaliser ca
	ft_fill_inst_addr(champ);
	ft_replace_direct(champ);
	return (SUCCESS);
}
