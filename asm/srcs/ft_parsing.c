/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:37:12 by pmilan            #+#    #+#             */
/*   Updated: 2018/07/16 16:13:18 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	get_champ_name_comment_other_lines(char **member, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(fd, &tmp) == GNL_SUCCESS)
	{
		if (!(*member = ft_str_and_free_join(*member, "\n")))
			exit(EXIT_FAILURE);
		if (!(*member = ft_str_and_free_join(*member, tmp)))
			exit(EXIT_FAILURE);
		if (ft_strchr(tmp, '"'))
			return (ft_name_comment_other_lines_next(member, tmp));
		free(tmp);
	}
	return (ERROR);
}

static int	get_champ_name_comment(char *line, char **member, int fd)
{
	int		i;

	i = 0;
	while (*line && *line != COMMENT_CHAR && *line != '"')
		line++;
	if (*line == COMMENT_CHAR)
		return (ERROR);
	if (*line == '\0')
		return (ERROR);
	line++;
	while (line[i] && line[i] != '"')
		++i;
	if (!(*member = ft_strndup(line, i)))
		exit(EXIT_FAILURE);
	if (line[i] == '\0')
		if (get_champ_name_comment_other_lines(member, fd) == ERROR)
			return (ERROR);
	if (line[i] != '\0' && line[i + 1])
	{
		while (line[++i])
			if (line[i] != ' ' && line[i] != '\t')
				return (ERROR);
	}
	return (SUCCESS);
}

static int	parse_line(char *line, t_champ *champ)
{
	int		status;
	int		i;

	status = SUCCESS;
	i = -1;
	while (line[++i])
		if (line[i] == COMMENT_CHAR || line[i + 1] == '\0')
			return (UNFINISHED);
		else if (line[i] != ' ' && line[i] != '\t')
			break ;
	if (ft_strstr(line, NAME_CMD_STRING) && !champ->name)
	{
		if (ft_verif_format_name(line) == SUCCESS)
			status = get_champ_name_comment(line, &champ->name, champ->fd);
		else
			return (ft_error(champ, "error: .name is badly spelled"));
	}
	else if (ft_strstr(line, COMMENT_CMD_STRING) && !champ->comment)
		if (ft_verif_format_comment(line) == SUCCESS)
			status = get_champ_name_comment(line, &champ->comment, champ->fd);
		else
			return (ft_error(champ, "error: .comment is badly spelled"));
	else if (line[i])
		return (ft_error(champ, "error: wrong command"));
	return (ft_parse_status(champ, status));
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

int			read_file(t_champ *champ)
{
	char	*line;
	int		stock;
	int		result_gnl;

	if ((champ->fd = open(champ->argv, O_RDONLY)) <= 0)
		return (ft_error(champ, "error: bad file descriptor"));
	line = NULL;
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
