/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:37:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/24 23:22:08 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void	get_champ_name_comment_other_lines(char **member, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(fd, &tmp) == GNL_SUCCESS)
	{
		if (!strchr(tmp, '"'))
			if (!(*member = ft_str_and_free_join(*member, "\n")))
				exit(EXIT_FAILURE);
		if (!(*member = ft_str_and_free_join(*member, tmp)))
			exit(EXIT_FAILURE);
		if (strchr(tmp, '"'))
		{
			(*member)[ft_strlen(*member) - 1] = '\0';
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

static int	get_champ_name_comment(char *line, char **member, int fd)
{
	int		i;

	i = 0;
	while (*line && *line != '"')
		line++;
	if (*line == '\0')
		return (ERROR);
	line++;
	while (line[i] && line[i] != '"')
		++i;
	if (!(*member = ft_strndup(line, i)))
		exit(EXIT_FAILURE);
	if (line[i] == '\0')
		get_champ_name_comment_other_lines(member, fd);
	return (SUCCESS);
}

static int	parse_line(char *line, t_champ *champ)
{
	int		status;

	status = SUCCESS;
	if (line[0] == COMMENT_CHAR)
		return (UNFINISHED);
	if (ft_strstr(line, ".name"))
		status = get_champ_name_comment(line, &champ->name, champ->fd);
	else if (ft_strstr(line, ".comment"))
		status = get_champ_name_comment(line, &champ->comment, champ->fd);
	if (status == ERROR)
		return (ft_error(champ, "error: name or comment is badly formatted"));
	if (champ->name && ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return (ft_error(champ, "error: program name is too long"));
	if (champ->comment && ft_strlen(champ->comment) > COMMENT_LENGTH)
		return (ft_error(champ, "error: program comment is too long"));
	if (champ->name != NULL && champ->comment != NULL)
		return (FINISHED);
	return (UNFINISHED);
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
		if ((stock = parse_line(line, champ)) == ERROR && ft_fruit(1, &line))
			return (ERROR);
		free(line);
		if (stock == FINISHED)
			break ;
	}
	if (result_gnl == GNL_ERROR)
		return (ft_error(champ, "error: bad file descriptor"));
	store_lines(champ);
	close(champ->fd);
	if (ft_check_input_format(champ) == ERROR)
		return (ERROR);
	if (ft_get_instru(champ) == ERROR)
		return (ft_error(champ, "error: instruction problem"));
	return (ft_fill_inst_addr_and_replace_direct(champ));
}
